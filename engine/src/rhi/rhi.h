#pragma once
#include <core/types.h>

/* ---- Handle: index + generation for safe resource reference ---- */
typedef struct { u32 index; u32 generation; } RHIHandle;

/* ---- Strongly-typed handle aliases ---- */
typedef RHIHandle RHIBuffer;
typedef RHIHandle RHIShader;
typedef RHIHandle RHIPipeline;
typedef RHIHandle RHITexture;
typedef RHIHandle RHIFramebuffer;
typedef RHIHandle RHIRenderPass;

#define RHI_HANDLE_NULL ((RHIHandle){0, 0})
#define rhi_handle_valid(h) ((h).generation != 0)

/* ---- Enums ---- */
typedef enum {
    RHI_BACKEND_OPENGL,
    RHI_BACKEND_VULKAN,
} RHIBackend;

typedef enum {
    RHI_FORMAT_R8G8B8A8_UNORM,
    RHI_FORMAT_B8G8R8A8_UNORM,
    RHI_FORMAT_R16G16B16A16_SFLOAT,
    RHI_FORMAT_D32_FLOAT,
    RHI_FORMAT_UNDEFINED,
} RHIFormat;

typedef enum {
    RHI_BUFFER_USAGE_VERTEX  = 1 << 0,
    RHI_BUFFER_USAGE_INDEX   = 1 << 1,
    RHI_BUFFER_USAGE_UNIFORM = 1 << 2,
    RHI_BUFFER_USAGE_TEXEL   = 1 << 3,
    RHI_BUFFER_USAGE_STORAGE = 1 << 4,
} RHIBufferUsage;

typedef enum {
    RHI_FILTER_NEAREST,
    RHI_FILTER_LINEAR,
} RHIFilter;

typedef enum {
    RHI_WRAP_REPEAT,
    RHI_WRAP_CLAMP_TO_EDGE,
} RHIWrapMode;

/* ---- Descriptors ---- */
typedef struct {
    RHIBufferUsage usage;
    usize          size;
    const void    *initial_data;
} RHIBufferDesc;

typedef struct {
    RHIShader vert;
    RHIShader frag;
    u32 vertex_stride;
    bool no_vertex_input;
    bool uses_textures;
    bool depth_compare_lequal;
    bool depth_write_disable;
    bool disable_culling;
    bool uses_texel_buffer;
    bool alpha_blend;
    bool font_vertex;
    bool is_instanced;
    bool skinned_vertex;
    bool is_compute;
    bool uses_storage;
    bool is_shadow_depth;
} RHIPipelineDesc;

typedef struct {
    u32         width;
    u32         height;
    RHIFormat   format;
    u32         mip_levels;
    const void *data;
} RHITextureDesc;

typedef struct {
    RHIFilter  min_filter;
    RHIFilter  mag_filter;
    RHIWrapMode wrap_u;
    RHIWrapMode wrap_v;
    RHIWrapMode wrap_w;
} RHISamplerDesc;

typedef RHIHandle RHISampler;

typedef RHIHandle RHICubemap;

/* ---- Command Buffer (opaque) ---- */
typedef struct RHICmdBuffer RHICmdBuffer;

/* ---- Device (opaque) ---- */
typedef struct RHIDevice RHIDevice;

/* ---- Device API ---- */
RHIDevice *rhi_device_create(RHIBackend backend, void *window_native, void *display_native, u32 w, u32 h);
void       rhi_device_destroy(RHIDevice *dev);
void       rhi_device_resize(RHIDevice *dev, u32 w, u32 h);

/* ---- Frame lifecycle ---- */
RHICmdBuffer *rhi_frame_begin(RHIDevice *dev);
void          rhi_frame_end(RHIDevice *dev);
void          rhi_present(RHIDevice *dev);

/* ---- Resource creation ---- */
RHIBuffer   rhi_buffer_create(RHIDevice *dev, const RHIBufferDesc *desc);
void        rhi_buffer_destroy(RHIDevice *dev, RHIBuffer buf);
RHIShader   rhi_shader_create(RHIDevice *dev, const char *source, usize len, bool is_fragment);
void        rhi_shader_destroy(RHIDevice *dev, RHIShader shader);
RHIPipeline rhi_pipeline_create(RHIDevice *dev, const RHIPipelineDesc *desc);
void        rhi_pipeline_destroy(RHIDevice *dev, RHIPipeline pipe);
RHITexture  rhi_texture_create(RHIDevice *dev, const RHITextureDesc *desc);
void        rhi_texture_destroy(RHIDevice *dev, RHITexture tex);
RHISampler  rhi_sampler_create(RHIDevice *dev, const RHISamplerDesc *desc);
void        rhi_sampler_destroy(RHIDevice *dev, RHISampler sampler);

/* ---- Command recording ---- */
void rhi_cmd_begin_render_pass(RHICmdBuffer *cmd);
void rhi_cmd_end_render_pass(RHICmdBuffer *cmd);
void rhi_cmd_bind_pipeline(RHICmdBuffer *cmd, RHIPipeline pipe);
void rhi_cmd_bind_vertex_buffer(RHICmdBuffer *cmd, RHIBuffer buf, usize offset);
void rhi_cmd_bind_index_buffer(RHICmdBuffer *cmd, RHIBuffer buf, usize offset);
void rhi_cmd_set_viewport(RHICmdBuffer *cmd, f32 x, f32 y, f32 w, f32 h);
void rhi_cmd_set_scissor(RHICmdBuffer *cmd, i32 x, i32 y, u32 w, u32 h);
void rhi_cmd_draw(RHICmdBuffer *cmd, u32 vertex_count, u32 instance_count);
void rhi_cmd_draw_indexed(RHICmdBuffer *cmd, u32 index_count, u32 instance_count);
void rhi_cmd_clear_color(RHICmdBuffer *cmd, f32 r, f32 g, f32 b, f32 a);
void rhi_cmd_bind_texture(RHICmdBuffer *cmd, RHITexture tex, RHISampler sampler, u32 unit);
void rhi_cmd_bind_shadow_texture(RHICmdBuffer *cmd, RHITexture shadow_tex, RHISampler sampler);
void rhi_cmd_bind_uniform_buffer(RHICmdBuffer *cmd, RHIBuffer buf, u32 binding);
void rhi_cmd_set_uniform_mat4(RHICmdBuffer *cmd, i32 location, const f32 *m);
void rhi_cmd_set_uniform_vec3(RHICmdBuffer *cmd, i32 location, f32 x, f32 y, f32 z);
void rhi_cmd_set_uniform_vec2(RHICmdBuffer *cmd, i32 location, f32 x, f32 y);
void rhi_cmd_set_uniform_vec4(RHICmdBuffer *cmd, i32 location, f32 x, f32 y, f32 z, f32 w);
void rhi_cmd_set_uniform_f32(RHICmdBuffer *cmd, i32 location, f32 v);
void rhi_cmd_set_uniform_i32(RHICmdBuffer *cmd, i32 location, i32 v);
i32  rhi_pipeline_get_uniform_location(RHIDevice *dev, RHIPipeline pipe, const char *name);

/* ---- Framebuffer (depth-only for shadow pass) ---- */
typedef struct {
    RHIFramebuffer fbo;
    RHITexture     depth_tex;
    u32            width;
    u32            height;
} RHIShadowMap;

RHIShadowMap rhi_shadow_map_create(RHIDevice *dev, u32 width, u32 height);
void         rhi_shadow_map_destroy(RHIDevice *dev, RHIShadowMap *sm);
void         rhi_cmd_bind_shadow_map(RHICmdBuffer *cmd, RHIShadowMap *sm);
void         rhi_cmd_unbind_shadow_map(RHICmdBuffer *cmd, u32 screen_w, u32 screen_h);
void rhi_cmd_clear_depth(RHICmdBuffer *cmd);

/* ---- Cubemap ---- */
typedef struct {
    u32         size;
    const void *faces[6];
} RHICubemapDesc;

RHICubemap rhi_cubemap_create(RHIDevice *dev, const RHICubemapDesc *desc);
void       rhi_cubemap_destroy(RHIDevice *dev, RHICubemap cm);
void rhi_cmd_bind_cubemap(RHICmdBuffer *cmd, RHICubemap cm, RHISampler sampler, u32 unit);

/* ---- Depth state ---- */
void rhi_cmd_set_depth_func_less_or_equal(RHICmdBuffer *cmd);
void rhi_cmd_set_depth_func_less(RHICmdBuffer *cmd);

/* ---- Texel buffer ---- */
void rhi_cmd_bind_texel_buffers(RHICmdBuffer *cmd, RHIBuffer buf0, RHIBuffer buf1);
void rhi_buffer_update(RHIDevice *dev, RHIBuffer buf, const void *data, usize size);

/* ---- Material textures (binds albedo/mr/normal/emissive + shadow in one descriptor set) ---- */
void rhi_cmd_bind_material_textures(RHICmdBuffer *cmd,
    RHITexture albedo, RHITexture mr, RHITexture normal, RHITexture emissive,
    RHITexture shadow, RHITexture ssao, RHISampler sampler);

void rhi_cmd_bind_textures_multi(RHICmdBuffer *cmd,
    RHITexture *textures, int count, RHISampler sampler);

/* ---- Offscreen framebuffer (color + depth) ---- */
typedef struct {
    RHIFramebuffer fb;
    RHITexture     color_tex;
    RHITexture     depth_tex;
    u32            width;
    u32            height;
} RHIOffscreenFBO;

RHIOffscreenFBO rhi_offscreen_fbo_create(RHIDevice *dev, u32 width, u32 height);
RHIOffscreenFBO rhi_offscreen_fbo_create_fmt(RHIDevice *dev, u32 width, u32 height, RHIFormat color_fmt);
void            rhi_offscreen_fbo_destroy(RHIDevice *dev, RHIOffscreenFBO *fbo);
void            rhi_offscreen_fbo_bind(RHICmdBuffer *cmd, RHIOffscreenFBO *fbo);
void            rhi_offscreen_fbo_unbind(RHICmdBuffer *cmd, u32 screen_w, u32 screen_h);

/* ---- Compute shader ---- */
RHIShader   rhi_shader_create_compute(RHIDevice *dev, const char *source, usize len);
void        rhi_cmd_dispatch(RHICmdBuffer *cmd, u32 x, u32 y, u32 z);
void        rhi_cmd_bind_storage_buffer(RHICmdBuffer *cmd, RHIBuffer buf, u32 binding);
void rhi_cmd_memory_barrier(RHICmdBuffer *cmd);
void rhi_cmd_transition_depth_to_read(RHICmdBuffer *cmd, RHITexture depth_tex);
void*       rhi_buffer_map(RHIDevice *dev, RHIBuffer buf);
void        rhi_buffer_unmap(RHIDevice *dev, RHIBuffer buf);
