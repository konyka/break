/* rhi_stubs.c — Minimal RHI stubs for tests.
 *
 * Satisfies the linker for tests that compile renderer modules
 * but don't exercise RHI code paths (test_cmd_buffer, test_lighting, etc.).
 */

#include <rhi/rhi.h>
#include <string.h>

void rhi_cmd_draw(RHICmdBuffer *cmd, u32 vc, u32 ic) { (void)cmd; (void)vc; (void)ic; }
void rhi_cmd_draw_indexed(RHICmdBuffer *cmd, u32 ic, u32 inst) { (void)cmd; (void)ic; (void)inst; }
void rhi_cmd_bind_pipeline(RHICmdBuffer *cmd, RHIPipeline p) { (void)cmd; (void)p; }
void rhi_cmd_bind_vertex_buffer(RHICmdBuffer *cmd, RHIBuffer b, usize o) { (void)cmd; (void)b; (void)o; }
void rhi_cmd_bind_index_buffer(RHICmdBuffer *cmd, RHIBuffer b, usize o) { (void)cmd; (void)b; (void)o; }
void rhi_cmd_bind_uniform_buffer(RHICmdBuffer *cmd, RHIBuffer b, u32 bind) { (void)cmd; (void)b; (void)bind; }
void rhi_cmd_bind_texture(RHICmdBuffer *cmd, RHITexture t, RHISampler s, u32 u) { (void)cmd; (void)t; (void)s; (void)u; }
void rhi_cmd_bind_material_textures(RHICmdBuffer *c, RHITexture a, RHITexture mr, RHITexture n, RHITexture e, RHITexture sh, RHITexture ss, RHISampler s) { (void)c; (void)a; (void)mr; (void)n; (void)e; (void)sh; (void)ss; (void)s; }
void rhi_cmd_set_scissor(RHICmdBuffer *cmd, i32 x, i32 y, u32 w, u32 h) { (void)cmd; (void)x; (void)y; (void)w; (void)h; }
void rhi_cmd_set_viewport(RHICmdBuffer *cmd, f32 x, f32 y, f32 w, f32 h) { (void)cmd; (void)x; (void)y; (void)w; (void)h; }
void rhi_cmd_set_shadow_viewport(RHICmdBuffer *cmd, u32 x, u32 y, u32 w, u32 h) { (void)cmd; (void)x; (void)y; (void)w; (void)h; }

/* Resource management stubs for modules that compile init/shutdown paths */
static RHIBuffer  stub_buffer  = {0, 0};
static RHIPipeline stub_pipeline = {0, 0};
static RHITexture  stub_texture  = {0, 0};
static RHISampler  stub_sampler  = {0, 0};
static RHIShader   stub_shader   = {0, 0};

RHIBuffer  rhi_buffer_create(RHIDevice *d, const RHIBufferDesc *desc)  { (void)d; (void)desc; return stub_buffer; }
void       rhi_buffer_destroy(RHIDevice *d, RHIBuffer b)               { (void)d; (void)b; }
void       rhi_buffer_update(RHIDevice *d, RHIBuffer b, const void *data, usize sz) { (void)d; (void)b; (void)data; (void)sz; }
void      *rhi_buffer_map(RHIDevice *d, RHIBuffer b)                   { (void)d; (void)b; return NULL; }
void       rhi_buffer_unmap(RHIDevice *d, RHIBuffer b)                 { (void)d; (void)b; }
void       rhi_cmd_copy_buffer(RHICmdBuffer *c, RHIBuffer s, RHIBuffer d, usize sz) { (void)c; (void)s; (void)d; (void)sz; }
void       rhi_buffer_update_region(RHIDevice *d, RHIBuffer b, usize off, const void *data, usize sz) { (void)d; (void)b; (void)off; (void)data; (void)sz; }

RHIPipeline rhi_pipeline_create(RHIDevice *d, const RHIPipelineDesc *desc) { (void)d; (void)desc; return stub_pipeline; }
void       rhi_pipeline_destroy(RHIDevice *d, RHIPipeline p)          { (void)d; (void)p; }
i32        rhi_pipeline_get_uniform_location(RHIDevice *d, RHIPipeline p, const char *n) { (void)d; (void)p; (void)n; return -1; }

RHITexture rhi_texture_create(RHIDevice *d, const RHITextureDesc *desc) { (void)d; (void)desc; return stub_texture; }
void       rhi_texture_destroy(RHIDevice *d, RHITexture t)              { (void)d; (void)t; }

RHISampler rhi_sampler_create(RHIDevice *d, const RHISamplerDesc *desc) { (void)d; (void)desc; return stub_sampler; }
void       rhi_sampler_destroy(RHIDevice *d, RHISampler s)              { (void)d; (void)s; }

RHIShader  rhi_shader_create(RHIDevice *d, const char *src, usize len, bool is_frag) { (void)d; (void)src; (void)len; (void)is_frag; return stub_shader; }
RHIShader  rhi_shader_create_compute(RHIDevice *d, const char *src, usize len) { (void)d; (void)src; (void)len; return stub_shader; }
void       rhi_shader_destroy(RHIDevice *d, RHIShader s)                { (void)d; (void)s; }

static RHIOffscreenFBO stub_offscreen_fbo = {{0,0}, {0,0}, {0,0}, 0, 0};

RHIOffscreenFBO rhi_offscreen_fbo_create(RHIDevice *d, u32 w, u32 h)    { (void)d; (void)w; (void)h; return stub_offscreen_fbo; }
RHIOffscreenFBO rhi_offscreen_fbo_create_fmt(RHIDevice *d, u32 w, u32 h, RHIFormat fmt) { (void)d; (void)w; (void)h; (void)fmt; return stub_offscreen_fbo; }
void       rhi_offscreen_fbo_destroy(RHIDevice *d, RHIOffscreenFBO *fbo) { (void)d; (void)fbo; }
void       rhi_offscreen_fbo_bind(RHICmdBuffer *c, RHIOffscreenFBO *fbo) { (void)c; (void)fbo; }
void       rhi_offscreen_fbo_unbind(RHICmdBuffer *c, u32 w, u32 h)    { (void)c; (void)w; (void)h; }

void rhi_cmd_set_uniform_f32(RHICmdBuffer *c, i32 loc, f32 v)          { (void)c; (void)loc; (void)v; }
void rhi_cmd_set_uniform_i32(RHICmdBuffer *c, i32 loc, i32 v)          { (void)c; (void)loc; (void)v; }
void rhi_cmd_set_uniform_vec2(RHICmdBuffer *c, i32 loc, f32 a, f32 b)  { (void)c; (void)loc; (void)a; (void)b; }
void rhi_cmd_set_uniform_vec3(RHICmdBuffer *c, i32 loc, f32 a, f32 b, f32 d) { (void)c; (void)loc; (void)a; (void)b; (void)d; }
void rhi_cmd_set_uniform_mat4(RHICmdBuffer *c, i32 loc, const f32 *m)  { (void)c; (void)loc; (void)m; }
void rhi_cmd_set_uniform_vec4(RHICmdBuffer *c, i32 loc, f32 a, f32 b, f32 d, f32 e) { (void)c; (void)loc; (void)a; (void)b; (void)d; (void)e; }
void rhi_cmd_bind_storage_buffer(RHICmdBuffer *c, RHIBuffer b, u32 bind) { (void)c; (void)b; (void)bind; }
void rhi_cmd_bind_texture_mip(RHICmdBuffer *c, RHITexture t, RHISampler s, u32 u, u32 mip) { (void)c; (void)t; (void)s; (void)u; (void)mip; }
void rhi_cmd_bind_texture_compute(RHICmdBuffer *c, RHITexture t, RHISampler s, u32 u) { (void)c; (void)t; (void)s; (void)u; }
void rhi_cmd_bind_image_texture(RHICmdBuffer *c, RHITexture t, u32 u, u32 mip, bool wo) { (void)c; (void)t; (void)u; (void)mip; (void)wo; }
void rhi_cmd_transition_depth_to_read(RHICmdBuffer *c, RHITexture t)   { (void)c; (void)t; }
void rhi_cmd_memory_barrier(RHICmdBuffer *c)                            { (void)c; }
void rhi_cmd_dispatch(RHICmdBuffer *c, u32 x, u32 y, u32 z)            { (void)c; (void)x; (void)y; (void)z; }
