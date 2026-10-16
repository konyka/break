/* engine_rhi_headless: fail-closed RHI backend (multi-backend RHI spec §4.1).
 * Every entry point refuses work: no GPU, no surface, no evidence. This
 * library exists so headless contract tests can link the full rhi_* symbol
 * surface without a real backend; it must never be cited as GPU evidence. */
#include <rhi/rhi.h>
#include <rhi/rhi_native_vulkan.h>

#include <string.h>

/* ---- device lifecycle ---- */
RHIDevice *rhi_device_create(RHIBackend backend, void *window_native,
                             void *display_native, u32 w, u32 h) {
    (void)backend; (void)window_native; (void)display_native; (void)w; (void)h;
    return NULL;
}
/* 计划 E Task 2：编译期单后端入口——headless fail-closed（契约测试期望 NULL）。
 * 双句柄（rhi.h）：headless 不消费任何句柄。 */
RHIDevice *rhi_device_create_compiled(void *window_native,
                                      void *surface_native,
                                      void *display_native, u32 w, u32 h) {
    (void)window_native; (void)surface_native; (void)display_native;
    (void)w; (void)h;
    return NULL;
}
void rhi_device_destroy(RHIDevice *dev) { (void)dev; }
void rhi_device_resize(RHIDevice *dev, u32 w, u32 h) {
    (void)dev; (void)w; (void)h;
}
RHICmdBuffer *rhi_frame_begin(RHIDevice *dev) { (void)dev; return NULL; }
void rhi_frame_end(RHIDevice *dev) { (void)dev; }
void rhi_present(RHIDevice *dev) { (void)dev; }
void rhi_set_vsync(RHIDevice *dev, bool enabled) { (void)dev; (void)enabled; }
u32 rhi_frame_index(RHIDevice *dev) { (void)dev; return 0u; }
bool rhi_device_idle(RHIDevice *dev) { (void)dev; return false; }
/* Fail closed: a live device handle on the headless backend is a bug;
 * reporting lost forces callers to wind down instead of spinning. */
bool rhi_device_lost(RHIDevice *dev) { (void)dev; return true; }

/* ---- backend native interop (declared in rhi_native_vulkan.h) ---- */
bool rhi_backend_get_native_device(const RHIDevice *dev, RHINativeDevice *out) {
    (void)dev; (void)out; return false;
}
bool rhi_backend_get_device_info(const RHIDevice *dev, RHIDeviceInfo *out) {
    (void)dev; (void)out; return false;
}
bool rhi_backend_texture_get_native_info(const RHIDevice *dev,
                                         RHITexture texture,
                                         RHITextureNativeInfo *out) {
    (void)dev; (void)texture; (void)out; return false;
}
bool rhi_backend_cmd_buffer_get_native_info(const RHIDevice *dev,
                                            const RHICmdBuffer *cmd,
                                            RHICmdBufferNativeInfo *out) {
    (void)dev; (void)cmd; (void)out; return false;
}
bool rhi_backend_cmd_build_blas_one_triangle(
    RHICmdBuffer *cmd, RHIDevice *dev, RHIAccelerationStructure blas,
    const RHIBLASOneTriangleDesc *desc,
    RHIBuffer scratch_buffer, usize scratch_offset) {
    (void)cmd; (void)dev; (void)blas; (void)desc;
    (void)scratch_buffer; (void)scratch_offset;
    return false;
}
u64 rhi_backend_acceleration_structure_get_device_address(
    RHIDevice *dev, RHIAccelerationStructure structure) {
    (void)dev; (void)structure; return 0u;
}
bool rhi_backend_tlas_one_instance_get_build_sizes(
    RHIDevice *dev, RHIBuffer instance_buffer,
    RHIAccelerationStructureBuildSizes *out_sizes) {
    (void)dev; (void)instance_buffer; (void)out_sizes; return false;
}
bool rhi_backend_cmd_build_tlas_one_instance(
    RHICmdBuffer *cmd, RHIDevice *dev, RHIAccelerationStructure tlas,
    RHIBuffer instance_buffer, RHIBuffer scratch_buffer, usize scratch_offset) {
    (void)cmd; (void)dev; (void)tlas; (void)instance_buffer;
    (void)scratch_buffer; (void)scratch_offset;
    return false;
}
bool rhi_backend_acceleration_structure_get_vk_handle(
    RHIDevice *dev, RHIAccelerationStructure structure, void **out_handle) {
    (void)dev; (void)structure; (void)out_handle; return false;
}
bool rhi_blas_one_triangle_get_build_sizes(
    RHIDevice *dev, const RHIBLASOneTriangleDesc *desc,
    RHIAccelerationStructureBuildSizes *out_sizes) {
    (void)dev; (void)desc; (void)out_sizes; return false;
}
RHIAccelerationStructure rhi_backend_acceleration_structure_create(
    RHIDevice *dev, const RHIAccelerationStructureDesc *desc) {
    (void)dev; (void)desc; return RHI_HANDLE_NULL;
}
void rhi_backend_acceleration_structure_destroy(
    RHIDevice *dev, RHIAccelerationStructure structure) {
    (void)dev; (void)structure;
}

u32 rhi_vk_validation_message_count(void) { return 0u; }
void rhi_vk_validation_message_count_reset(void) {}
bool rhi_vk_validation_gate_active(void) { return false; }
void rhi_vk_validation_set_enabled(bool enabled) { (void)enabled; }

/* ---- resource creation ---- */
RHIBuffer rhi_buffer_create(RHIDevice *dev, const RHIBufferDesc *desc) {
    (void)dev; (void)desc; return RHI_HANDLE_NULL;
}
void rhi_buffer_destroy(RHIDevice *dev, RHIBuffer buf) { (void)dev; (void)buf; }
RHIShader rhi_shader_create(RHIDevice *dev, const char *source, usize len,
                            bool is_fragment) {
    (void)dev; (void)source; (void)len; (void)is_fragment;
    return RHI_HANDLE_NULL;
}
RHIShader rhi_shader_create_compute(RHIDevice *dev, const char *source,
                                    usize len) {
    (void)dev; (void)source; (void)len; return RHI_HANDLE_NULL;
}
void rhi_shader_destroy(RHIDevice *dev, RHIShader shader) {
    (void)dev; (void)shader;
}
RHIPipeline rhi_pipeline_create(RHIDevice *dev, const RHIPipelineDesc *desc) {
    (void)dev; (void)desc; return RHI_HANDLE_NULL;
}
void rhi_pipeline_destroy(RHIDevice *dev, RHIPipeline pipe) {
    (void)dev; (void)pipe;
}
RHITexture rhi_texture_create(RHIDevice *dev, const RHITextureDesc *desc) {
    (void)dev; (void)desc; return RHI_HANDLE_NULL;
}
void rhi_texture_destroy(RHIDevice *dev, RHITexture tex) {
    (void)dev; (void)tex;
}
RHITexture rhi_texture_array_create(RHIDevice *dev, u32 width, u32 height,
                                    u32 layers, RHIFormat fmt) {
    (void)dev; (void)width; (void)height; (void)layers; (void)fmt;
    return RHI_HANDLE_NULL;
}
void rhi_texture_array_upload_layer(RHIDevice *dev, RHITexture tex, u32 layer,
                                    const void *rgba8, usize size) {
    (void)dev; (void)tex; (void)layer; (void)rgba8; (void)size;
}
bool rhi_texture_get_size(RHIDevice *dev, RHITexture tex, u32 *out_w,
                          u32 *out_h) {
    (void)dev; (void)tex; (void)out_w; (void)out_h; return false;
}
bool rhi_texture_read_pixels(RHIDevice *dev, RHITexture tex, void *dst_rgba8,
                             usize size) {
    (void)dev; (void)tex; (void)dst_rgba8; (void)size; return false;
}
void rhi_texture_upload_mip(RHIDevice *dev, RHITexture tex, u32 mip_level,
                            u32 width, u32 height, const void *data,
                            usize size) {
    (void)dev; (void)tex; (void)mip_level; (void)width; (void)height;
    (void)data; (void)size;
}
RHISampler rhi_sampler_create(RHIDevice *dev, const RHISamplerDesc *desc) {
    (void)dev; (void)desc; return RHI_HANDLE_NULL;
}
void rhi_sampler_destroy(RHIDevice *dev, RHISampler sampler) {
    (void)dev; (void)sampler;
}

/* ---- command recording ---- */
void rhi_cmd_begin_render_pass(RHICmdBuffer *cmd) { (void)cmd; }
void rhi_cmd_end_render_pass(RHICmdBuffer *cmd) { (void)cmd; }
void rhi_cmd_bind_pipeline(RHICmdBuffer *cmd, RHIPipeline pipe) {
    (void)cmd; (void)pipe;
}
void rhi_cmd_bind_vertex_buffer(RHICmdBuffer *cmd, RHIBuffer buf,
                                usize offset) {
    (void)cmd; (void)buf; (void)offset;
}
void rhi_cmd_bind_index_buffer(RHICmdBuffer *cmd, RHIBuffer buf, usize offset,
                               bool is_u32) {
    (void)cmd; (void)buf; (void)offset; (void)is_u32;
}
void rhi_cmd_set_viewport(RHICmdBuffer *cmd, f32 x, f32 y, f32 w, f32 h,
                          f32 min_depth, f32 max_depth) {
    (void)cmd; (void)x; (void)y; (void)w; (void)h; (void)min_depth;
    (void)max_depth;
}
void rhi_cmd_set_scissor(RHICmdBuffer *cmd, i32 x, i32 y, u32 w, u32 h) {
    (void)cmd; (void)x; (void)y; (void)w; (void)h;
}
void rhi_cmd_set_scissor_top_left(RHICmdBuffer *cmd, u32 x, u32 y, u32 w,
                                  u32 h) {
    (void)cmd; (void)x; (void)y; (void)w; (void)h;
}
void rhi_cmd_set_shadow_viewport(RHICmdBuffer *cmd, u32 x, u32 y, u32 w,
                                 u32 h) {
    (void)cmd; (void)x; (void)y; (void)w; (void)h;
}
void rhi_cmd_draw(RHICmdBuffer *cmd, u32 vertex_count, u32 instance_count) {
    (void)cmd; (void)vertex_count; (void)instance_count;
}
void rhi_cmd_draw_base(RHICmdBuffer *cmd, u32 vertex_count, u32 instance_count,
                       u32 first_vertex) {
    (void)cmd; (void)vertex_count; (void)instance_count; (void)first_vertex;
}
void rhi_cmd_draw_indexed(RHICmdBuffer *cmd, u32 index_count,
                          u32 instance_count) {
    (void)cmd; (void)index_count; (void)instance_count;
}
void rhi_cmd_draw_indexed_base(RHICmdBuffer *cmd, u32 index_count,
                               u32 instance_count, u32 first_index,
                               i32 vertex_offset) {
    (void)cmd; (void)index_count; (void)instance_count; (void)first_index;
    (void)vertex_offset;
}
void rhi_cmd_draw_indirect(RHIDevice *dev, RHIBuffer cmd_buf, u32 offset,
                           u32 draw_count, u32 stride) {
    (void)dev; (void)cmd_buf; (void)offset; (void)draw_count; (void)stride;
}
void rhi_cmd_draw_indexed_indirect(RHIDevice *dev, RHIBuffer cmd_buf,
                                   u32 offset, u32 draw_count, u32 stride) {
    (void)dev; (void)cmd_buf; (void)offset; (void)draw_count; (void)stride;
}
void rhi_cmd_draw_indexed_indirect_count(RHIDevice *dev, RHIBuffer cmd_buf,
                                         u32 cmd_offset, RHIBuffer count_buf,
                                         u32 count_offset, u32 max_draws,
                                         u32 stride) {
    (void)dev; (void)cmd_buf; (void)cmd_offset; (void)count_buf;
    (void)count_offset; (void)max_draws; (void)stride;
}
void rhi_cmd_clear_color(RHICmdBuffer *cmd, f32 r, f32 g, f32 b, f32 a) {
    (void)cmd; (void)r; (void)g; (void)b; (void)a;
}
void rhi_cmd_clear_color_attachment(RHICmdBuffer *cmd, u32 attachment, f32 r,
                                    f32 g, f32 b, f32 a) {
    (void)cmd; (void)attachment; (void)r; (void)g; (void)b; (void)a;
}
void rhi_cmd_bind_texture(RHICmdBuffer *cmd, RHITexture tex,
                          RHISampler sampler, u32 unit) {
    (void)cmd; (void)tex; (void)sampler; (void)unit;
}
void rhi_cmd_bind_shadow_texture(RHICmdBuffer *cmd, RHITexture shadow_tex,
                                 RHISampler sampler) {
    (void)cmd; (void)shadow_tex; (void)sampler;
}
void rhi_cmd_bind_uniform_buffer(RHICmdBuffer *cmd, RHIBuffer buf,
                                 u32 binding) {
    (void)cmd; (void)buf; (void)binding;
}
void rhi_cmd_set_uniform_mat4(RHICmdBuffer *cmd, i32 location, const f32 *m) {
    (void)cmd; (void)location; (void)m;
}
void rhi_cmd_set_uniform_vec3(RHICmdBuffer *cmd, i32 location, f32 x, f32 y,
                              f32 z) {
    (void)cmd; (void)location; (void)x; (void)y; (void)z;
}
void rhi_cmd_set_uniform_vec2(RHICmdBuffer *cmd, i32 location, f32 x, f32 y) {
    (void)cmd; (void)location; (void)x; (void)y;
}
void rhi_cmd_set_uniform_vec4(RHICmdBuffer *cmd, i32 location, f32 x, f32 y,
                              f32 z, f32 w) {
    (void)cmd; (void)location; (void)x; (void)y; (void)z; (void)w;
}
void rhi_cmd_set_uniform_f32(RHICmdBuffer *cmd, i32 location, f32 v) {
    (void)cmd; (void)location; (void)v;
}
void rhi_cmd_set_uniform_i32(RHICmdBuffer *cmd, i32 location, i32 v) {
    (void)cmd; (void)location; (void)v;
}
void rhi_cmd_push_constants(RHICmdBuffer *cmd, u32 offset, const void *data,
                            u32 size) {
    (void)cmd; (void)offset; (void)data; (void)size;
}
void rhi_cmd_set_uniform_bytes(RHICmdBuffer *cmd, i32 location,
                               const void *data, u32 size) {
    (void)cmd; (void)location; (void)data; (void)size;
}
i32 rhi_pipeline_get_uniform_location(RHIDevice *dev, RHIPipeline pipe,
                                      const char *name) {
    (void)dev; (void)pipe; (void)name; return -1;
}

/* Plan E Task 5: reflection-driven bindings — headless fail-closed stubs
 * (create NULL / resolve -1 / destroy no-op), mirroring the legacy stub above. */
RHIPipelineBindings *rhi_pipeline_bindings_create(RHIDevice *dev, RHIPipeline pipe) {
    (void)dev; (void)pipe; return NULL;
}

void rhi_pipeline_bindings_destroy(RHIDevice *dev, RHIPipelineBindings *b) {
    (void)dev; (void)b;
}

i32 rhi_pipeline_bindings_resolve(const RHIPipelineBindings *b, const char *name) {
    (void)b; (void)name; return -1;
}

/* ---- shadow map / cubemap / FBO ---- */
RHIShadowMap rhi_shadow_map_create(RHIDevice *dev, u32 width, u32 height) {
    RHIShadowMap out;
    (void)dev; (void)width; (void)height;
    memset(&out, 0, sizeof(out));
    return out;
}
void rhi_shadow_map_destroy(RHIDevice *dev, RHIShadowMap *sm) {
    (void)dev; (void)sm;
}
void rhi_cmd_bind_shadow_map(RHICmdBuffer *cmd, RHIShadowMap *sm) {
    (void)cmd; (void)sm;
}
void rhi_cmd_unbind_shadow_map(RHICmdBuffer *cmd, u32 screen_w, u32 screen_h) {
    (void)cmd; (void)screen_w; (void)screen_h;
}
void rhi_cmd_clear_depth(RHICmdBuffer *cmd) { (void)cmd; }
RHICubemap rhi_cubemap_create(RHIDevice *dev, const RHICubemapDesc *desc) {
    (void)dev; (void)desc; return RHI_HANDLE_NULL;
}
void rhi_cubemap_destroy(RHIDevice *dev, RHICubemap cm) {
    (void)dev; (void)cm;
}
void rhi_cubemap_transition_to_read(RHIDevice *dev, RHICubemap cm) {
    (void)dev; (void)cm;
}
void rhi_texture_transition_to_read(RHIDevice *dev, RHITexture tex) {
    (void)dev; (void)tex;
}
void rhi_cmd_bind_cubemap(RHICmdBuffer *cmd, RHICubemap cm,
                          RHISampler sampler, u32 unit) {
    (void)cmd; (void)cm; (void)sampler; (void)unit;
}
void rhi_cmd_set_depth_func_less_or_equal(RHICmdBuffer *cmd) { (void)cmd; }
void rhi_cmd_set_depth_func_less(RHICmdBuffer *cmd) { (void)cmd; }
void rhi_cmd_set_depth_mask(RHICmdBuffer *cmd, bool enabled) {
    (void)cmd; (void)enabled;
}
void rhi_cmd_set_cull_face(RHICmdBuffer *cmd, bool enabled) {
    (void)cmd; (void)enabled;
}

/* ---- buffers / texel ---- */
void rhi_cmd_bind_texel_buffers(RHICmdBuffer *cmd, RHIBuffer buf0,
                                RHIBuffer buf1) {
    (void)cmd; (void)buf0; (void)buf1;
}
void rhi_buffer_update(RHIDevice *dev, RHIBuffer buf, const void *data,
                       usize size) {
    (void)dev; (void)buf; (void)data; (void)size;
}
void rhi_buffer_update_region(RHIDevice *dev, RHIBuffer buf, usize offset,
                              const void *data, usize size) {
    (void)dev; (void)buf; (void)offset; (void)data; (void)size;
}
bool rhi_buffer_read(RHIDevice *dev, RHIBuffer buf, void *dst, usize offset,
                     usize size) {
    (void)dev; (void)buf; (void)dst; (void)offset; (void)size; return false;
}
void rhi_cmd_fill_buffer(RHICmdBuffer *cmd, RHIBuffer buf, usize offset,
                         usize size, u32 value) {
    (void)cmd; (void)buf; (void)offset; (void)size; (void)value;
}
void rhi_cmd_update_buffer(RHICmdBuffer *cmd, RHIBuffer buf, usize offset,
                           const void *data, usize size) {
    (void)cmd; (void)buf; (void)offset; (void)data; (void)size;
}
void *rhi_buffer_map(RHIDevice *dev, RHIBuffer buf) {
    (void)dev; (void)buf; return NULL;
}
void rhi_buffer_unmap(RHIDevice *dev, RHIBuffer buf) { (void)dev; (void)buf; }
void rhi_cmd_copy_buffer(RHICmdBuffer *cmd, RHIBuffer src, RHIBuffer dst,
                         usize size) {
    (void)cmd; (void)src; (void)dst; (void)size;
}

/* ---- material texture binders ---- */
void rhi_cmd_bind_material_textures(RHICmdBuffer *cmd, RHITexture albedo,
    RHITexture mr, RHITexture normal, RHITexture emissive, RHITexture shadow,
    RHITexture ssao, RHISampler sampler) {
    (void)cmd; (void)albedo; (void)mr; (void)normal; (void)emissive;
    (void)shadow; (void)ssao; (void)sampler;
}
void rhi_cmd_bind_material_textures_ibl(RHICmdBuffer *cmd, RHITexture albedo,
    RHITexture mr, RHITexture normal, RHITexture emissive,
    RHITexture occlusion, RHITexture shadow, RHITexture ssao,
    RHISampler sampler, RHITexture brdf_lut, RHICubemap irradiance_map,
    RHICubemap prefilter_map, const RHITexture *point_shadow_cubes,
    u32 point_shadow_count) {
    (void)cmd; (void)albedo; (void)mr; (void)normal; (void)emissive;
    (void)occlusion; (void)shadow; (void)ssao; (void)sampler; (void)brdf_lut;
    (void)irradiance_map; (void)prefilter_map; (void)point_shadow_cubes;
    (void)point_shadow_count;
}
void rhi_cmd_bind_deferred_gbuf_textures(RHICmdBuffer *cmd,
    RHITexture albedo_metallic, RHITexture roughness_ao, RHITexture normal,
    RHITexture depth, RHITexture emissive, RHITexture shadow, RHITexture ssao,
    RHISampler sampler, RHITexture brdf_lut, RHICubemap irradiance_map,
    RHICubemap prefilter_map, const RHITexture *point_shadow_cubes,
    u32 point_shadow_count, RHISampler cube_sampler) {
    (void)cmd; (void)albedo_metallic; (void)roughness_ao; (void)normal;
    (void)depth; (void)emissive; (void)shadow; (void)ssao; (void)sampler;
    (void)brdf_lut; (void)irradiance_map; (void)prefilter_map;
    (void)point_shadow_cubes; (void)point_shadow_count; (void)cube_sampler;
}
void rhi_cmd_bind_textures_multi(RHICmdBuffer *cmd, RHITexture *textures,
                                 int count, RHISampler sampler) {
    (void)cmd; (void)textures; (void)count; (void)sampler;
}

/* ---- offscreen / MRT / depth-cube FBO ---- */
RHIOffscreenFBO rhi_offscreen_fbo_create(RHIDevice *dev, u32 width,
                                         u32 height) {
    RHIOffscreenFBO out;
    (void)dev; (void)width; (void)height;
    memset(&out, 0, sizeof(out));
    return out;
}
RHIOffscreenFBO rhi_offscreen_fbo_create_fmt(RHIDevice *dev, u32 width,
                                             u32 height, RHIFormat color_fmt) {
    RHIOffscreenFBO out;
    (void)dev; (void)width; (void)height; (void)color_fmt;
    memset(&out, 0, sizeof(out));
    return out;
}
RHIOffscreenFBO rhi_offscreen_fbo_create_desc(RHIDevice *dev,
                                              const RHIOffscreenFBODesc *desc) {
    RHIOffscreenFBO out;
    (void)dev; (void)desc;
    memset(&out, 0, sizeof(out));
    return out;
}
void rhi_offscreen_fbo_destroy(RHIDevice *dev, RHIOffscreenFBO *fbo) {
    (void)dev; (void)fbo;
}
void rhi_offscreen_fbo_bind(RHICmdBuffer *cmd, RHIOffscreenFBO *fbo) {
    (void)cmd; (void)fbo;
}
void rhi_offscreen_fbo_bind_load(RHICmdBuffer *cmd, RHIOffscreenFBO *fbo) {
    (void)cmd; (void)fbo;
}
void rhi_offscreen_fbo_unbind(RHICmdBuffer *cmd, u32 screen_w, u32 screen_h) {
    (void)cmd; (void)screen_w; (void)screen_h;
}
void rhi_offscreen_fbo_set_clear_color(RHIDevice *dev, RHIOffscreenFBO *fbo,
                                       f32 r, f32 g, f32 b, f32 a) {
    (void)dev; (void)fbo; (void)r; (void)g; (void)b; (void)a;
}
RHIMRTFBO rhi_mrt_fbo_create(RHIDevice *dev, u32 width, u32 height,
                             const RHIFormat *formats, u32 attachment_count) {
    RHIMRTFBO out;
    (void)dev; (void)width; (void)height; (void)formats;
    (void)attachment_count;
    memset(&out, 0, sizeof(out));
    return out;
}
void rhi_mrt_fbo_destroy(RHIDevice *dev, RHIMRTFBO *fbo) {
    (void)dev; (void)fbo;
}
void rhi_mrt_fbo_bind(RHICmdBuffer *cmd, RHIMRTFBO *fbo) {
    (void)cmd; (void)fbo;
}
void rhi_mrt_fbo_bind_load(RHICmdBuffer *cmd, RHIMRTFBO *fbo) {
    (void)cmd; (void)fbo;
}
void rhi_mrt_fbo_unbind(RHICmdBuffer *cmd, u32 screen_w, u32 screen_h) {
    (void)cmd; (void)screen_w; (void)screen_h;
}
RHICubemapDepthFBO rhi_cubemap_depth_fbo_create(RHIDevice *dev, u32 size) {
    RHICubemapDepthFBO out;
    (void)dev; (void)size;
    memset(&out, 0, sizeof(out));
    return out;
}
void rhi_cubemap_depth_fbo_destroy(RHIDevice *dev, RHICubemapDepthFBO *fbo) {
    (void)dev; (void)fbo;
}
void rhi_cubemap_depth_fbo_bind_face(RHICmdBuffer *cmd,
                                     RHICubemapDepthFBO *fbo, u32 face) {
    (void)cmd; (void)fbo; (void)face;
}
void rhi_cubemap_depth_fbo_unbind(RHICmdBuffer *cmd, u32 screen_w,
                                  u32 screen_h) {
    (void)cmd; (void)screen_w; (void)screen_h;
}

/* ---- compute ---- */
void rhi_cmd_dispatch(RHICmdBuffer *cmd, u32 x, u32 y, u32 z) {
    (void)cmd; (void)x; (void)y; (void)z;
}
void rhi_cmd_bind_storage_buffer(RHICmdBuffer *cmd, RHIBuffer buf,
                                 u32 binding) {
    (void)cmd; (void)buf; (void)binding;
}
void rhi_cmd_bind_acceleration_structure(RHICmdBuffer *cmd,
                                         RHIAccelerationStructure structure,
                                         u32 binding) {
    (void)cmd; (void)structure; (void)binding;
}
void rhi_cmd_memory_barrier(RHICmdBuffer *cmd) { (void)cmd; }
void rhi_cmd_bind_image_texture(RHICmdBuffer *cmd, RHITexture tex, u32 unit,
                                u32 mip_level, bool write_only) {
    (void)cmd; (void)tex; (void)unit; (void)mip_level; (void)write_only;
}
void rhi_cmd_bind_image_cubemap_face(RHICmdBuffer *cmd, RHICubemap cm,
                                     u32 face, u32 mip, u32 unit,
                                     bool write_only) {
    (void)cmd; (void)cm; (void)face; (void)mip; (void)unit; (void)write_only;
}
void rhi_cmd_bind_cubemap_sampler(RHICmdBuffer *cmd, RHICubemap cm,
                                  RHISampler sampler, u32 unit) {
    (void)cmd; (void)cm; (void)sampler; (void)unit;
}
void rhi_cmd_bind_texture_mip(RHICmdBuffer *cmd, RHITexture tex,
                              RHISampler sampler, u32 unit, u32 mip_level) {
    (void)cmd; (void)tex; (void)sampler; (void)unit; (void)mip_level;
}
void rhi_cmd_bind_texture_compute(RHICmdBuffer *cmd, RHITexture tex,
                                  RHISampler sampler, u32 unit) {
    (void)cmd; (void)tex; (void)sampler; (void)unit;
}
void rhi_cmd_transition_depth_to_read(RHICmdBuffer *cmd,
                                      RHITexture depth_tex) {
    (void)cmd; (void)depth_tex;
}

/* ---- screenshot ---- */
bool rhi_screenshot(RHIDevice *dev, u32 x, u32 y, u32 w, u32 h, u8 *pixels,
                    usize pixel_bytes) {
    (void)dev; (void)x; (void)y; (void)w; (void)h; (void)pixels;
    (void)pixel_bytes;
    return false;
}

/* ---- GPU timer ---- */
RHIGPUTimer *rhi_gpu_timer_create(RHIDevice *dev) { (void)dev; return NULL; }
void rhi_gpu_timer_destroy(RHIDevice *dev, RHIGPUTimer *t) {
    (void)dev; (void)t;
}
void rhi_gpu_timer_begin(RHIGPUTimer *t) { (void)t; }
void rhi_gpu_timer_end(RHIGPUTimer *t) { (void)t; }
f64 rhi_gpu_timer_elapsed_ms(RHIGPUTimer *t) { (void)t; return 0.0; }

/* ---- ENGINE_RHI_TEST hooks (GL cache owner contract, headless flavor) ---- */
#ifdef ENGINE_RHI_TEST
static RHIDevice *g_headless_gl_cache_owner;
void rhi_test_gl_cache_sync(RHIDevice *dev) { g_headless_gl_cache_owner = dev; }
RHIDevice *rhi_test_gl_cache_owner(void) { return g_headless_gl_cache_owner; }
#endif
