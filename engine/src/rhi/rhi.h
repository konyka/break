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
    RHI_FORMAT_R32_FLOAT,
    RHI_FORMAT_D32_FLOAT,
    RHI_FORMAT_UNDEFINED,
} RHIFormat;

typedef enum {
    RHI_BUFFER_USAGE_VERTEX   = 1 << 0,
    RHI_BUFFER_USAGE_INDEX    = 1 << 1,
    RHI_BUFFER_USAGE_UNIFORM  = 1 << 2,
    RHI_BUFFER_USAGE_TEXEL    = 1 << 3,
    RHI_BUFFER_USAGE_STORAGE  = 1 << 4,
    RHI_BUFFER_USAGE_INDIRECT = 1 << 5,
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
    bool wireframe;
    bool point_list;             /* R168-C: POINT_LIST topology (particles) */
    /* Dedicated Vulkan push-constant layouts (see rhi_pipeline_get_uniform_location).
     * Ignored by the GL backend, which reflects uniform names directly. */
    bool terrain_layout;
    bool water_layout;
    bool combined_aa_layout;     /* combined_taa_fxaa_vk.frag push block */
    bool combined_color_layout;  /* combined_color_vk.frag push block */
    /* Color attachment format of the render target this pipeline draws into.
     * Used by the Vulkan backend for render-pass compatibility: a pipeline must
     * be created against a render pass whose color format matches the FBO it is
     * bound in. The default value (RHI_FORMAT_R8G8B8A8_UNORM == 0) selects the
     * swapchain pass; set RHI_FORMAT_R16G16B16A16_SFLOAT for the HDR scene FBO.
     * Ignored by the GL backend. */
    RHIFormat color_format;
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
void          rhi_set_vsync(RHIDevice *dev, bool enabled);
/* R172: In-flight frame slot index (Vulkan 0..1 after fence wait; GL always 0). */
u32           rhi_frame_index(RHIDevice *dev);

/* ---- Resource creation ---- */
RHIBuffer   rhi_buffer_create(RHIDevice *dev, const RHIBufferDesc *desc);
void        rhi_buffer_destroy(RHIDevice *dev, RHIBuffer buf);
RHIShader   rhi_shader_create(RHIDevice *dev, const char *source, usize len, bool is_fragment);
void        rhi_shader_destroy(RHIDevice *dev, RHIShader shader);
RHIPipeline rhi_pipeline_create(RHIDevice *dev, const RHIPipelineDesc *desc);
void        rhi_pipeline_destroy(RHIDevice *dev, RHIPipeline pipe);
RHITexture  rhi_texture_create(RHIDevice *dev, const RHITextureDesc *desc);
void        rhi_texture_destroy(RHIDevice *dev, RHITexture tex);
/* Upload RGBA8 pixel data into a single mip level of an existing texture.
 * Used by the mipmap streaming system to push individual levels to the GPU. */
void        rhi_texture_upload_mip(RHIDevice *dev, RHITexture tex, u32 mip_level,
                                   u32 width, u32 height, const void *data, usize size);
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
/* Set a non-Y-flipped viewport + matching scissor, matching the depth/shadow
 * render-pass convention (top-left origin on VK, native on GL). Used to render
 * cascaded-shadow quadrants into a single shadow-atlas texture. */
void rhi_cmd_set_shadow_viewport(RHICmdBuffer *cmd, u32 x, u32 y, u32 w, u32 h);
void rhi_cmd_draw(RHICmdBuffer *cmd, u32 vertex_count, u32 instance_count);
void rhi_cmd_draw_indexed(RHICmdBuffer *cmd, u32 index_count, u32 instance_count);
/* ---- Indirect drawing (GPU-driven pipeline) ---- */
/* Non-indexed DrawIndirect (VkDrawIndirectCommand / DrawArraysIndirect). */
void rhi_cmd_draw_indirect(RHIDevice *dev, RHIBuffer cmd_buf, u32 offset,
                           u32 draw_count, u32 stride);
void rhi_cmd_draw_indexed_indirect(RHIDevice *dev, RHIBuffer cmd_buf, u32 offset,
                                   u32 draw_count, u32 stride);
void rhi_cmd_draw_indexed_indirect_count(RHIDevice *dev, RHIBuffer cmd_buf, u32 cmd_offset,
                                         RHIBuffer count_buf, u32 count_offset,
                                         u32 max_draws, u32 stride);
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
/* R179: Raw push-constant / uniform blob (VK byte offset; GL no-op). */
void rhi_cmd_set_uniform_bytes(RHICmdBuffer *cmd, i32 location, const void *data, u32 size);
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
    /* Optional. 0 (RHI_FORMAT_R8G8B8A8_UNORM) keeps the legacy RGBA8 behavior.
     * Set RHI_FORMAT_R16G16B16A16_SFLOAT for HDR env/IBL cubemaps. */
    RHIFormat   format;
    /* Optional. 0 or 1 == single mip. >1 allocates a mip chain (e.g. IBL
     * prefilter).  When >1 and faces[] are provided, only mip 0 is uploaded. */
    u32         mip_levels;
} RHICubemapDesc;

RHICubemap rhi_cubemap_create(RHIDevice *dev, const RHICubemapDesc *desc);
void       rhi_cubemap_destroy(RHIDevice *dev, RHICubemap cm);
/* Transition all faces/mips of a cubemap that was written via compute storage
 * (GENERAL layout) back to a shader-readable layout for sampling.  Performs a
 * device-idle one-time submit; call once after IBL generation completes. */
void       rhi_cubemap_transition_to_read(RHIDevice *dev, RHICubemap cm);

/* Transition a 2D texture written via compute storage (GENERAL layout) back to
 * a shader-readable layout for sampling.  Device-idle one-time submit. */
void       rhi_texture_transition_to_read(RHIDevice *dev, RHITexture tex);
void rhi_cmd_bind_cubemap(RHICmdBuffer *cmd, RHICubemap cm, RHISampler sampler, u32 unit);

/* ---- Depth state ---- */
void rhi_cmd_set_depth_func_less_or_equal(RHICmdBuffer *cmd);
void rhi_cmd_set_depth_func_less(RHICmdBuffer *cmd);
void rhi_cmd_set_depth_mask(RHICmdBuffer *cmd, bool enabled);
void rhi_cmd_set_cull_face(RHICmdBuffer *cmd, bool enabled);

/* ---- Texel buffer ---- */
void rhi_cmd_bind_texel_buffers(RHICmdBuffer *cmd, RHIBuffer buf0, RHIBuffer buf1);
void rhi_buffer_update(RHIDevice *dev, RHIBuffer buf, const void *data, usize size);
void rhi_buffer_update_region(RHIDevice *dev, RHIBuffer buf, usize offset, const void *data, usize size);
/* R171: Recorded GPU clear (vkCmdFillBuffer / glClearBufferSubData). Host
 * memcpy updates are NOT ordered between dispatches in the same Vulkan CB. */
void rhi_cmd_fill_buffer(RHICmdBuffer *cmd, RHIBuffer buf, usize offset, usize size, u32 value);
/* R183: Record a host→GPU buffer write into the command buffer (ordered vs
 * later dispatches). Prefer over rhi_buffer_update when the same buffer is
 * rewritten multiple times in one CB (e.g. CSM cascade visibility). */
void rhi_cmd_update_buffer(RHICmdBuffer *cmd, RHIBuffer buf, usize offset,
                           const void *data, usize size);

/* ---- Material textures (binds albedo/mr/normal/emissive + shadow in one descriptor set) ---- */
void rhi_cmd_bind_material_textures(RHICmdBuffer *cmd,
    RHITexture albedo, RHITexture mr, RHITexture normal, RHITexture emissive,
    RHITexture shadow, RHITexture ssao, RHISampler sampler);

/* Material + IBL textures: binds material (0-4) + shadow (1) + ssao (11) +
 * brdf_lut/irradiance/prefilter (7-9) + point_shadow_cubes (10-13). */
void rhi_cmd_bind_material_textures_ibl(RHICmdBuffer *cmd,
    RHITexture albedo, RHITexture mr, RHITexture normal, RHITexture emissive,
    RHITexture shadow, RHITexture ssao, RHISampler sampler,
    RHITexture brdf_lut, RHICubemap irradiance_map, RHICubemap prefilter_map,
    const RHITexture *point_shadow_cubes, u32 point_shadow_count);

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

/* ---- MRT (Multiple Render Targets) framebuffer ---- */
#define RHI_MRT_MAX_ATTACHMENTS 4

typedef struct {
    RHIFramebuffer fb;
    RHITexture     color_tex[RHI_MRT_MAX_ATTACHMENTS];
    RHITexture     depth_tex;
    u32            attachment_count;
    u32            width;
    u32            height;
} RHIMRTFBO;

RHIMRTFBO rhi_mrt_fbo_create(RHIDevice *dev, u32 width, u32 height,
                              const RHIFormat *formats, u32 attachment_count);
void      rhi_mrt_fbo_destroy(RHIDevice *dev, RHIMRTFBO *fbo);
void      rhi_mrt_fbo_bind(RHICmdBuffer *cmd, RHIMRTFBO *fbo);
void      rhi_mrt_fbo_unbind(RHICmdBuffer *cmd, u32 screen_w, u32 screen_h);

/* ---- Depth cubemap FBO (point-light shadow maps) ---- */
typedef struct {
    RHIFramebuffer fb;
    RHITexture     depth_tex;   /* cubemap depth texture */
    u32            size;        /* face width == face height */
} RHICubemapDepthFBO;

RHICubemapDepthFBO rhi_cubemap_depth_fbo_create(RHIDevice *dev, u32 size);
void               rhi_cubemap_depth_fbo_destroy(RHIDevice *dev, RHICubemapDepthFBO *fbo);
/* Bind a single cubemap face for rendering (face 0..5 = +X,-X,+Y,-Y,+Z,-Z). */
void               rhi_cubemap_depth_fbo_bind_face(RHICmdBuffer *cmd, RHICubemapDepthFBO *fbo, u32 face);
void               rhi_cubemap_depth_fbo_unbind(RHICmdBuffer *cmd, u32 screen_w, u32 screen_h);

/* ---- Compute shader ---- */
RHIShader   rhi_shader_create_compute(RHIDevice *dev, const char *source, usize len);
void        rhi_cmd_dispatch(RHICmdBuffer *cmd, u32 x, u32 y, u32 z);
void        rhi_cmd_bind_storage_buffer(RHICmdBuffer *cmd, RHIBuffer buf, u32 binding);
void rhi_cmd_memory_barrier(RHICmdBuffer *cmd);
void rhi_cmd_bind_image_texture(RHICmdBuffer *cmd, RHITexture tex, u32 unit, u32 mip_level, bool write_only);
/* Bind a cubemap face's mip level as a storage image for compute write
 * (face 0..5 = +X,-X,+Y,-Y,+Z,-Z). mip 0 is the base level. */
void rhi_cmd_bind_image_cubemap_face(RHICmdBuffer *cmd, RHICubemap cm, u32 face, u32 mip, u32 unit, bool write_only);
/* Bind a cubemap as a sampler for compute read (binding 1 in sampler_mip set). */
void rhi_cmd_bind_cubemap_sampler(RHICmdBuffer *cmd, RHICubemap cm, RHISampler sampler, u32 unit);
void rhi_cmd_bind_texture_mip(RHICmdBuffer *cmd, RHITexture tex, RHISampler sampler, u32 unit, u32 mip_level);
/* Bind a full 2D texture (mip 0) as a sampler for a *compute* pipeline's
 * sampler set. Unlike rhi_cmd_bind_texture (which targets the graphics
 * material set), this targets the compute sampler_mip set and assumes the
 * texture is already in a shader-read layout (no transition barrier). */
void rhi_cmd_bind_texture_compute(RHICmdBuffer *cmd, RHITexture tex, RHISampler sampler, u32 unit);
void rhi_cmd_transition_depth_to_read(RHICmdBuffer *cmd, RHITexture depth_tex);
void*       rhi_buffer_map(RHIDevice *dev, RHIBuffer buf);
void        rhi_buffer_unmap(RHIDevice *dev, RHIBuffer buf);
void        rhi_cmd_copy_buffer(RHICmdBuffer *cmd, RHIBuffer src, RHIBuffer dst, usize size);
void        rhi_screenshot(RHIDevice *dev, u32 x, u32 y, u32 w, u32 h, u8 *pixels);

typedef struct RHIGPUTimer RHIGPUTimer;
RHIGPUTimer *rhi_gpu_timer_create(RHIDevice *dev);
void         rhi_gpu_timer_destroy(RHIDevice *dev, RHIGPUTimer *t);
void         rhi_gpu_timer_begin(RHIGPUTimer *t);
void         rhi_gpu_timer_end(RHIGPUTimer *t);
f64          rhi_gpu_timer_elapsed_ms(RHIGPUTimer *t);
