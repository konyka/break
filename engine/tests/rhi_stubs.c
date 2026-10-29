/* rhi_stubs.c — Minimal RHI stubs for tests.
 *
 * Satisfies the linker for tests that compile renderer modules
 * but don't exercise RHI code paths (test_cmd_buffer, test_lighting, etc.).
 */

#include <rhi/rhi.h>
#include <string.h>

#ifdef BREAK_EDITOR_SHELL_TESTING
#include "rhi_editor_fake.h"
#endif

u32 g_stub_draw_base_calls = 0;
u32 g_stub_draw_base_last_vertex_count = 0;
u32 g_stub_draw_base_last_instance_count = 0;
u32 g_stub_draw_base_last_first_vertex = 0;
void rhi_cmd_draw(RHICmdBuffer *cmd, u32 vc, u32 ic) { (void)cmd; (void)vc; (void)ic; }
void rhi_cmd_draw_base(RHICmdBuffer *cmd, u32 vc, u32 ic, u32 fv) {
    (void)cmd;
    g_stub_draw_base_calls++;
    g_stub_draw_base_last_vertex_count = vc;
    g_stub_draw_base_last_instance_count = ic;
    g_stub_draw_base_last_first_vertex = fv;
}
void rhi_cmd_draw_indexed(RHICmdBuffer *cmd, u32 ic, u32 inst) { (void)cmd; (void)ic; (void)inst; }
void rhi_cmd_draw_indexed_base(RHICmdBuffer *cmd, u32 ic, u32 inst, u32 fi, i32 vo) {
    (void)cmd; (void)ic; (void)inst; (void)fi; (void)vo;
}
void rhi_cmd_draw_indexed_instanced_base(RHICmdBuffer *cmd, u32 ic, u32 inst, u32 fi,
                                         i32 vo, u32 first_instance) {
    (void)cmd; (void)ic; (void)inst; (void)fi; (void)vo; (void)first_instance;
}
void rhi_cmd_bind_pipeline(RHICmdBuffer *cmd, RHIPipeline p) { (void)cmd; (void)p; }
void rhi_cmd_bind_vertex_buffer(RHICmdBuffer *cmd, RHIBuffer b, usize o) { (void)cmd; (void)b; (void)o; }
void rhi_cmd_bind_index_buffer(RHICmdBuffer *cmd, RHIBuffer b, usize o, bool is_u32) {
    (void)cmd; (void)b; (void)o; (void)is_u32;
}
void rhi_cmd_bind_uniform_buffer(RHICmdBuffer *cmd, RHIBuffer b, u32 bind) { (void)cmd; (void)b; (void)bind; }
void rhi_cmd_bind_texture(RHICmdBuffer *cmd, RHITexture t, RHISampler s, u32 u) { (void)cmd; (void)t; (void)s; (void)u; }
void rhi_cmd_bind_material_textures(RHICmdBuffer *c, RHITexture a, RHITexture mr, RHITexture n, RHITexture e, RHITexture sh, RHITexture ss, RHISampler s) { (void)c; (void)a; (void)mr; (void)n; (void)e; (void)sh; (void)ss; (void)s; }
void rhi_cmd_set_scissor(RHICmdBuffer *cmd, i32 x, i32 y, u32 w, u32 h) { (void)cmd; (void)x; (void)y; (void)w; (void)h; }
void rhi_cmd_set_scissor_top_left(RHICmdBuffer *cmd, u32 x, u32 y, u32 w, u32 h) {
    (void)cmd; (void)x; (void)y; (void)w; (void)h;
}
void rhi_cmd_set_viewport(RHICmdBuffer *cmd, f32 x, f32 y, f32 w, f32 h,
                          f32 min_d, f32 max_d) {
    (void)cmd; (void)x; (void)y; (void)w; (void)h; (void)min_d; (void)max_d;
}
void rhi_cmd_set_shadow_viewport(RHICmdBuffer *cmd, u32 x, u32 y, u32 w, u32 h) { (void)cmd; (void)x; (void)y; (void)w; (void)h; }

/* Resource management stubs for modules that compile init/shutdown paths */
static RHIBuffer  stub_buffer  = {0, 0};
static RHIPipeline stub_pipeline = {0, 0};
static RHITexture  stub_texture  = {0, 0};
static RHISampler  stub_sampler  = {0, 0};
static RHIShader   stub_shader   = {0, 0};

#ifdef BREAK_EDITOR_SHELL_TESTING
#define EDITOR_RHI_FAKE_CAPACITY 64u
#define EDITOR_RHI_FAKE_LINK_FAIL (1u << 0)
#define EDITOR_RHI_FAKE_BINDINGS_FAIL (1u << 1)
#define EDITOR_RHI_FAKE_NO_MVP (1u << 2)
#define EDITOR_RHI_FAKE_NO_COLOR (1u << 3)
#define EDITOR_RHI_FAKE_HAS_REVISION (1u << 4)

typedef struct {
    RHIHandle handle;
    u32 revision, flags;
    u32 vertex_revision, fragment_revision; /* pipelines only */
    bool fragment;                          /* shaders only */
    bool live;
} EditorRhiFakeObject;

struct RHIPipelineBindings {
    RHIPipeline pipeline;
    bool live;
};

static struct {
    bool enabled;
    u32 next_generation;
    EditorRhiFakeStats stats;
    EditorRhiFakeObject shaders[EDITOR_RHI_FAKE_CAPACITY];
    EditorRhiFakeObject pipelines[EDITOR_RHI_FAKE_CAPACITY];
    EditorRhiFakeObject buffers[EDITOR_RHI_FAKE_CAPACITY];
    EditorRhiFakeObject textures[EDITOR_RHI_FAKE_CAPACITY];
    u32 texture_create_failures;
    RHIPipelineBindings bindings[EDITOR_RHI_FAKE_CAPACITY];
} g_editor_rhi_fake;

static bool editor_rhi_fake_contains(const char *src, usize len,
                                     const char *marker) {
    usize marker_len = strlen(marker);
    usize i;
    if (src == NULL || marker_len > len) {
        return false;
    }
    for (i = 0u; i < len && len - i >= marker_len; i++) {
        if (memcmp(src + i, marker, marker_len) == 0) {
            return true;
        }
    }
    return false;
}

static bool editor_rhi_fake_read_revision(const char *src, usize len,
                                          u32 *revision) {
    usize i;
    if (src == NULL || revision == NULL) {
        return false;
    }
    for (i = 0u; i < len && len - i >= 4u; i++) {
        usize j;
        u64 value = 0u;
        if (memcmp(src + i, "REV=", 4u) != 0) {
            continue;
        }
        j = i + 4u;
        if (j == len || src[j] < '0' || src[j] > '9') {
            continue;
        }
        while (j < len && src[j] >= '0' && src[j] <= '9') {
            value = value * 10u + (u64)(src[j] - '0');
            if (value > 0xffffffffu) {
                value = 0xffffffffu;
            }
            j++;
        }
        *revision = (u32)value;
        return true;
    }
    return false;
}

static u32 editor_rhi_fake_source_flags(const char *src, usize len) {
    u32 flags = 0u;
    u32 revision = 0u;
    if (editor_rhi_fake_contains(src, len, "LINK_FAIL")) {
        flags |= EDITOR_RHI_FAKE_LINK_FAIL;
    }
    if (editor_rhi_fake_contains(src, len, "BINDINGS_FAIL")) {
        flags |= EDITOR_RHI_FAKE_BINDINGS_FAIL;
    }
    if (editor_rhi_fake_contains(src, len, "NO_MVP")) {
        flags |= EDITOR_RHI_FAKE_NO_MVP;
    }
    if (editor_rhi_fake_contains(src, len, "NO_COLOR")) {
        flags |= EDITOR_RHI_FAKE_NO_COLOR;
    }
    if (editor_rhi_fake_read_revision(src, len, &revision)) {
        flags |= EDITOR_RHI_FAKE_HAS_REVISION;
    }
    return flags;
}

static i32 editor_rhi_fake_find(const EditorRhiFakeObject *objects,
                                RHIHandle handle) {
    u32 i;
    if (!rhi_handle_valid(handle)) {
        return -1;
    }
    for (i = 0u; i < EDITOR_RHI_FAKE_CAPACITY; i++) {
        if (objects[i].live && objects[i].handle.index == handle.index &&
            objects[i].handle.generation == handle.generation) {
            return (i32)i;
        }
    }
    return -1;
}

static RHIHandle editor_rhi_fake_object_create(EditorRhiFakeObject *objects,
                                               u32 flags, u32 revision) {
    u32 i;
    for (i = 0u; i < EDITOR_RHI_FAKE_CAPACITY; i++) {
        if (!objects[i].live) {
            g_editor_rhi_fake.next_generation++;
            if (g_editor_rhi_fake.next_generation == 0u) {
                g_editor_rhi_fake.next_generation++;
            }
            objects[i].handle.index = i + 1u;
            objects[i].handle.generation = g_editor_rhi_fake.next_generation;
            objects[i].flags = flags;
            objects[i].revision = revision;
            objects[i].live = true;
            return objects[i].handle;
        }
    }
    return RHI_HANDLE_NULL;
}

void editor_rhi_fake_reset(void) {
    memset(&g_editor_rhi_fake, 0, sizeof(g_editor_rhi_fake));
}

void editor_rhi_fake_set_enabled(bool enabled) {
    g_editor_rhi_fake.enabled = enabled;
}

bool editor_rhi_fake_texture_live(RHITexture texture) {
    return editor_rhi_fake_find(g_editor_rhi_fake.textures, texture) >= 0;
}

void editor_rhi_fake_fail_texture_creates(u32 n) {
    g_editor_rhi_fake.texture_create_failures = n;
}

void editor_rhi_fake_stats(EditorRhiFakeStats *out) {
    if (out != NULL) {
        *out = g_editor_rhi_fake.stats;
    }
}

u32 editor_rhi_fake_pipeline_revision(RHIPipeline pipeline) {
    i32 slot = editor_rhi_fake_find(g_editor_rhi_fake.pipelines, pipeline);
    return slot >= 0 ? g_editor_rhi_fake.pipelines[slot].revision : 0u;
}

u32 editor_rhi_fake_pipeline_stage_revision(RHIPipeline pipeline,
                                            bool fragment) {
    i32 slot = editor_rhi_fake_find(g_editor_rhi_fake.pipelines, pipeline);
    if (slot < 0) {
        return 0u;
    }
    return fragment ? g_editor_rhi_fake.pipelines[slot].fragment_revision
                    : g_editor_rhi_fake.pipelines[slot].vertex_revision;
}
#endif

RHIBuffer rhi_buffer_create(RHIDevice *d, const RHIBufferDesc *desc) {
    (void)d;
#ifdef BREAK_EDITOR_SHELL_TESTING
    if (g_editor_rhi_fake.enabled) {
        RHIBuffer buffer;
        if (desc == NULL) {
            return RHI_HANDLE_NULL;
        }
        buffer = editor_rhi_fake_object_create(g_editor_rhi_fake.buffers, 0u, 0u);
        if (rhi_handle_valid(buffer)) {
            g_editor_rhi_fake.stats.buffer_creates++;
            g_editor_rhi_fake.stats.live_buffers++;
        }
        return buffer;
    }
#endif
    (void)desc;
    return stub_buffer;
}

void rhi_buffer_destroy(RHIDevice *d, RHIBuffer b) {
    (void)d;
#ifdef BREAK_EDITOR_SHELL_TESTING
    if (g_editor_rhi_fake.enabled) {
        i32 slot = editor_rhi_fake_find(g_editor_rhi_fake.buffers, b);
        if (slot >= 0) {
            g_editor_rhi_fake.buffers[slot].live = false;
            g_editor_rhi_fake.stats.live_buffers--;
        }
        return;
    }
#endif
    (void)b;
}
void       rhi_buffer_update(RHIDevice *d, RHIBuffer b, const void *data, usize sz) { (void)d; (void)b; (void)data; (void)sz; }
void      *rhi_buffer_map(RHIDevice *d, RHIBuffer b)                   { (void)d; (void)b; return NULL; }
void       rhi_buffer_unmap(RHIDevice *d, RHIBuffer b)                 { (void)d; (void)b; }
bool       rhi_buffer_read(RHIDevice *d, RHIBuffer b, void *dst, usize off, usize sz) {
    (void)d; (void)b; (void)dst; (void)off; (void)sz; return false;
}
void       rhi_cmd_copy_buffer(RHICmdBuffer *c, RHIBuffer s, RHIBuffer d, usize sz) { (void)c; (void)s; (void)d; (void)sz; }
void       rhi_cmd_fill_buffer(RHICmdBuffer *c, RHIBuffer b, usize off, usize sz, u32 v) { (void)c; (void)b; (void)off; (void)sz; (void)v; }
void       rhi_cmd_update_buffer(RHICmdBuffer *c, RHIBuffer b, usize off, const void *d, usize sz) {
    (void)c; (void)b; (void)off; (void)d; (void)sz;
}
void       rhi_buffer_update_region(RHIDevice *d, RHIBuffer b, usize off, const void *data, usize sz) { (void)d; (void)b; (void)off; (void)data; (void)sz; }
u32        rhi_frame_index(RHIDevice *d) { (void)d; return 0u; }

RHIPipeline rhi_pipeline_create(RHIDevice *d, const RHIPipelineDesc *desc) {
    (void)d;
#ifdef BREAK_EDITOR_SHELL_TESTING
    if (g_editor_rhi_fake.enabled) {
        i32 vert_slot, frag_slot;
        u32 flags, revision;
        RHIPipeline pipeline;
        if (desc == NULL) {
            return RHI_HANDLE_NULL;
        }
        vert_slot = editor_rhi_fake_find(g_editor_rhi_fake.shaders, desc->vert);
        frag_slot = editor_rhi_fake_find(g_editor_rhi_fake.shaders, desc->frag);
        if (vert_slot < 0 || frag_slot < 0) {
            return RHI_HANDLE_NULL;
        }
        flags = g_editor_rhi_fake.shaders[vert_slot].flags |
                g_editor_rhi_fake.shaders[frag_slot].flags;
        if ((flags & EDITOR_RHI_FAKE_LINK_FAIL) != 0u) {
            return RHI_HANDLE_NULL;
        }
        revision = (g_editor_rhi_fake.shaders[vert_slot].flags &
                    EDITOR_RHI_FAKE_HAS_REVISION) != 0u
                       ? g_editor_rhi_fake.shaders[vert_slot].revision
                       : g_editor_rhi_fake.shaders[frag_slot].revision;
        /* stage-swapped descriptors are a caller bug the fake must expose */
        if (g_editor_rhi_fake.shaders[vert_slot].fragment ||
            !g_editor_rhi_fake.shaders[frag_slot].fragment) {
            return RHI_HANDLE_NULL;
        }
        pipeline = editor_rhi_fake_object_create(
            g_editor_rhi_fake.pipelines, flags, revision);
        if (rhi_handle_valid(pipeline)) {
            EditorRhiFakeObject *p =
                &g_editor_rhi_fake.pipelines[pipeline.index - 1u];
            p->vertex_revision = g_editor_rhi_fake.shaders[vert_slot].revision;
            p->fragment_revision = g_editor_rhi_fake.shaders[frag_slot].revision;
            g_editor_rhi_fake.stats.pipeline_creates++;
            g_editor_rhi_fake.stats.live_pipelines++;
        }
        return pipeline;
    }
#endif
    (void)desc;
    return stub_pipeline;
}

void rhi_pipeline_destroy(RHIDevice *d, RHIPipeline p) {
    (void)d;
#ifdef BREAK_EDITOR_SHELL_TESTING
    if (g_editor_rhi_fake.enabled) {
        i32 slot = editor_rhi_fake_find(g_editor_rhi_fake.pipelines, p);
        if (slot >= 0) {
            g_editor_rhi_fake.pipelines[slot].live = false;
            g_editor_rhi_fake.stats.live_pipelines--;
            g_editor_rhi_fake.stats.pipeline_destroys++;
        }
        return;
    }
#endif
    (void)p;
}

i32 rhi_pipeline_get_uniform_location(RHIDevice *d, RHIPipeline p, const char *n) { (void)d; (void)p; (void)n; return -1; }

/* Plan E Task 5: reflection-driven bindings — fail-closed like the legacy
 * uniform-location stub above (create -> NULL, resolve -> -1). */
bool rhi_device_get_capabilities(const RHIDevice *d, RHICapabilities *out) {
    (void)d;
    if (out != NULL) {
        memset(out, 0, sizeof(*out));
    }
#ifdef BREAK_EDITOR_SHELL_TESTING
    if (g_editor_rhi_fake.enabled) {
        if (out == NULL) {
            return false;
        }
        out->shader_variant = (u32)RHI_SHADER_VARIANT_GLSL;
        return true;
    }
#endif
    return false;
}
/* Render debugger read-only queries: fail closed like the caps stub. */
bool       rhi_device_get_info(const RHIDevice *d, RHIDeviceInfo *out) { (void)d; if (out) memset(out, 0, sizeof(*out)); return false; }
RHIDeviceStatus rhi_device_get_status(const RHIDevice *d) { (void)d; return RHI_DEVICE_STATUS_UNKNOWN; }
bool       rhi_device_resource_usage(const RHIDevice *d, u32 *used, u32 *cap) { (void)d; if (used) *used = 0u; if (cap) *cap = 0u; return false; }
const char *rhi_rollout_compiled_backend(void) { return "none"; }
const char *rhi_rollout_compiled_reason(void) { return "none"; }

RHIPipelineBindings *rhi_pipeline_bindings_create(RHIDevice *d, RHIPipeline p) {
    (void)d;
#ifdef BREAK_EDITOR_SHELL_TESTING
    if (g_editor_rhi_fake.enabled) {
        i32 pipeline_slot = editor_rhi_fake_find(g_editor_rhi_fake.pipelines, p);
        u32 i;
        if (pipeline_slot < 0 ||
            (g_editor_rhi_fake.pipelines[pipeline_slot].flags &
             EDITOR_RHI_FAKE_BINDINGS_FAIL) != 0u) {
            return NULL;
        }
        for (i = 0u; i < EDITOR_RHI_FAKE_CAPACITY; i++) {
            if (!g_editor_rhi_fake.bindings[i].live) {
                g_editor_rhi_fake.bindings[i].pipeline = p;
                g_editor_rhi_fake.bindings[i].live = true;
                g_editor_rhi_fake.stats.live_bindings++;
                return &g_editor_rhi_fake.bindings[i];
            }
        }
        return NULL;
    }
#endif
    (void)p;
    return NULL;
}

void rhi_pipeline_bindings_destroy(RHIDevice *d, RHIPipelineBindings *b) {
    (void)d;
#ifdef BREAK_EDITOR_SHELL_TESTING
    if (g_editor_rhi_fake.enabled) {
        u32 i;
        for (i = 0u; i < EDITOR_RHI_FAKE_CAPACITY; i++) {
            if (b == &g_editor_rhi_fake.bindings[i] &&
                g_editor_rhi_fake.bindings[i].live) {
                g_editor_rhi_fake.bindings[i].live = false;
                g_editor_rhi_fake.stats.live_bindings--;
                g_editor_rhi_fake.stats.binding_destroys++;
                return;
            }
        }
        return;
    }
#endif
    (void)b;
}

i32 rhi_pipeline_bindings_resolve(const RHIPipelineBindings *b, const char *n) {
#ifdef BREAK_EDITOR_SHELL_TESTING
    if (g_editor_rhi_fake.enabled) {
        i32 pipeline_slot;
        u32 flags;
        if (b == NULL || !b->live || n == NULL) {
            return -1;
        }
        pipeline_slot = editor_rhi_fake_find(g_editor_rhi_fake.pipelines,
                                             b->pipeline);
        if (pipeline_slot < 0) {
            return -1;
        }
        flags = g_editor_rhi_fake.pipelines[pipeline_slot].flags;
        if (strcmp(n, "u_mvp") == 0) {
            return (flags & EDITOR_RHI_FAKE_NO_MVP) != 0u ? -1 : 16;
        }
        if (strcmp(n, "u_color") == 0) {
            return (flags & EDITOR_RHI_FAKE_NO_COLOR) != 0u ? -1 : 32;
        }
        return -1;
    }
#endif
    (void)b;
    (void)n;
    return -1;
}

RHITexture rhi_texture_create(RHIDevice *d, const RHITextureDesc *desc) {
    (void)d;
#ifdef BREAK_EDITOR_SHELL_TESTING
    if (g_editor_rhi_fake.enabled) {
        RHITexture t;
        if (desc == NULL || desc->width == 0u || desc->height == 0u) {
            return RHI_HANDLE_NULL;
        }
        if (g_editor_rhi_fake.texture_create_failures > 0u) {
            g_editor_rhi_fake.texture_create_failures--;
            return RHI_HANDLE_NULL;
        }
        t = editor_rhi_fake_object_create(g_editor_rhi_fake.textures, 0u, 0u);
        if (rhi_handle_valid(t)) {
            g_editor_rhi_fake.stats.texture_creates++;
            g_editor_rhi_fake.stats.live_textures++;
            g_editor_rhi_fake.stats.last_texture_w = desc->width;
            g_editor_rhi_fake.stats.last_texture_h = desc->height;
            g_editor_rhi_fake.stats.last_texture_mips =
                desc->mip_levels > 0u ? desc->mip_levels : 1u;
        }
        return t;
    }
#endif
    (void)desc;
    return stub_texture;
}
void rhi_texture_destroy(RHIDevice *d, RHITexture t) {
    (void)d;
#ifdef BREAK_EDITOR_SHELL_TESTING
    if (g_editor_rhi_fake.enabled) {
        i32 slot = editor_rhi_fake_find(g_editor_rhi_fake.textures, t);
        if (slot >= 0) {
            g_editor_rhi_fake.textures[slot].live = false;
            g_editor_rhi_fake.stats.texture_destroys++;
            g_editor_rhi_fake.stats.live_textures--;
        }
        return;
    }
#endif
    (void)t;
}

RHISampler rhi_sampler_create(RHIDevice *d, const RHISamplerDesc *desc) { (void)d; (void)desc; return stub_sampler; }
void       rhi_sampler_destroy(RHIDevice *d, RHISampler s)              { (void)d; (void)s; }

RHIShader rhi_shader_create(RHIDevice *d, const char *src, usize len,
                            bool is_frag) {
    (void)d;
#ifndef BREAK_EDITOR_SHELL_TESTING
    (void)is_frag;
#endif
#ifdef BREAK_EDITOR_SHELL_TESTING
    if (g_editor_rhi_fake.enabled) {
        u32 revision = 0u;
        u32 flags;
        RHIShader shader;
        if (src == NULL ||
            editor_rhi_fake_contains(src, len, "COMPILE_FAIL")) {
            return RHI_HANDLE_NULL;
        }
        flags = editor_rhi_fake_source_flags(src, len);
        (void)editor_rhi_fake_read_revision(src, len, &revision);
        shader = editor_rhi_fake_object_create(g_editor_rhi_fake.shaders,
                                               flags, revision);
        if (rhi_handle_valid(shader)) {
            g_editor_rhi_fake.shaders[shader.index - 1u].fragment = is_frag;
            g_editor_rhi_fake.stats.live_shaders++;
        }
        return shader;
    }
#endif
    (void)src;
    (void)len;
    return stub_shader;
}
RHIShader  rhi_shader_create_compute(RHIDevice *d, const char *src, usize len) { (void)d; (void)src; (void)len; return stub_shader; }
/* Path-based siblings: the stub is argument-blind by design (see the rest of
 * this file), so these mirror rhi_shader_create / _compute rather than
 * inventing a stricter rule for the path form alone. */
RHIShader  rhi_shader_create_path(RHIDevice *d, const char *path, bool is_frag) { (void)d; (void)path; (void)is_frag; return stub_shader; }
RHIShader  rhi_shader_create_compute_path(RHIDevice *d, const char *path) { (void)d; (void)path; return stub_shader; }

void rhi_shader_destroy(RHIDevice *d, RHIShader s) {
    (void)d;
#ifdef BREAK_EDITOR_SHELL_TESTING
    if (g_editor_rhi_fake.enabled) {
        i32 slot = editor_rhi_fake_find(g_editor_rhi_fake.shaders, s);
        if (slot >= 0) {
            g_editor_rhi_fake.shaders[slot].live = false;
            g_editor_rhi_fake.stats.live_shaders--;
        }
        return;
    }
#endif
    (void)s;
}

RHICubemapDepthFBO rhi_cubemap_depth_fbo_create(RHIDevice *d, u32 size) { RHICubemapDepthFBO o; (void)d; memset(&o, 0, sizeof(o)); o.size = size; return o; }
void rhi_cubemap_depth_fbo_destroy(RHIDevice *d, RHICubemapDepthFBO *f) { (void)d; (void)f; }
void rhi_cubemap_depth_fbo_bind_face(RHICmdBuffer *c, RHICubemapDepthFBO *f, u32 face) { (void)c; (void)f; (void)face; }
void rhi_cubemap_depth_fbo_unbind(RHICmdBuffer *c, u32 w, u32 h) { (void)c; (void)w; (void)h; }

static RHIOffscreenFBO stub_offscreen_fbo = {{0,0}, {0,0}, {0,0}, 0, 0, 1};

RHIOffscreenFBO rhi_offscreen_fbo_create(RHIDevice *d, u32 w, u32 h)    { (void)d; (void)w; (void)h; return stub_offscreen_fbo; }
RHIOffscreenFBO rhi_offscreen_fbo_create_fmt(RHIDevice *d, u32 w, u32 h, RHIFormat fmt) {
    (void)d;
    (void)w;
    (void)h;
    (void)fmt;
#ifdef BREAK_EDITOR_SHELL_TESTING
    if (g_editor_rhi_fake.enabled) {
        RHIOffscreenFBO fbo = {{1, 1}, {2, 1}, {3, 1}, w, h, 1};
        return fbo;
    }
#endif
    return stub_offscreen_fbo;
}
void       rhi_offscreen_fbo_destroy(RHIDevice *d, RHIOffscreenFBO *fbo) { (void)d; (void)fbo; }
void       rhi_offscreen_fbo_bind(RHICmdBuffer *c, RHIOffscreenFBO *fbo) { (void)c; (void)fbo; }
void       rhi_offscreen_fbo_bind_load(RHICmdBuffer *c, RHIOffscreenFBO *fbo) { (void)c; (void)fbo; }
void       rhi_offscreen_fbo_unbind(RHICmdBuffer *c, u32 w, u32 h)    { (void)c; (void)w; (void)h; }

void rhi_cmd_set_uniform_f32(RHICmdBuffer *c, i32 loc, f32 v)          { (void)c; (void)loc; (void)v; }
void rhi_cmd_set_uniform_i32(RHICmdBuffer *c, i32 loc, i32 v)          { (void)c; (void)loc; (void)v; }
void rhi_cmd_set_uniform_vec2(RHICmdBuffer *c, i32 loc, f32 a, f32 b)  { (void)c; (void)loc; (void)a; (void)b; }
void rhi_cmd_set_uniform_vec3(RHICmdBuffer *c, i32 loc, f32 a, f32 b, f32 d) { (void)c; (void)loc; (void)a; (void)b; (void)d; }
void rhi_cmd_set_uniform_mat4(RHICmdBuffer *c, i32 loc, const f32 *m)  { (void)c; (void)loc; (void)m; }
void rhi_cmd_set_uniform_bytes(RHICmdBuffer *c, i32 loc, const void *data, u32 size) {
    (void)c; (void)loc; (void)data; (void)size;
}
/* R444: record rhi_cmd_push_constants calls so replay tests can assert the
 * RHI contract (offset/size/data) without a device. */
u32 g_stub_push_constants_calls = 0;
u32 g_stub_push_constants_last_offset = 0;
u32 g_stub_push_constants_last_size = 0;
u8  g_stub_push_constants_last_data[256];
void rhi_cmd_push_constants(RHICmdBuffer *c, u32 offset, const void *data, u32 size) {
    (void)c;
    g_stub_push_constants_calls++;
    g_stub_push_constants_last_offset = offset;
    g_stub_push_constants_last_size = size;
    if (data && size > 0u && size <= sizeof(g_stub_push_constants_last_data)) {
        memcpy(g_stub_push_constants_last_data, data, size);
    }
}
void rhi_cmd_set_uniform_vec4(RHICmdBuffer *c, i32 loc, f32 a, f32 b, f32 d, f32 e) { (void)c; (void)loc; (void)a; (void)b; (void)d; (void)e; }
void rhi_cmd_bind_storage_buffer(RHICmdBuffer *c, RHIBuffer b, u32 bind) { (void)c; (void)b; (void)bind; }
void rhi_cmd_bind_texture_mip(RHICmdBuffer *c, RHITexture t, RHISampler s, u32 u, u32 mip) { (void)c; (void)t; (void)s; (void)u; (void)mip; }
void rhi_cmd_bind_texture_compute(RHICmdBuffer *c, RHITexture t, RHISampler s, u32 u) { (void)c; (void)t; (void)s; (void)u; }
void rhi_cmd_bind_image_texture(RHICmdBuffer *c, RHITexture t, u32 u, u32 mip, bool wo) { (void)c; (void)t; (void)u; (void)mip; (void)wo; }
void rhi_cmd_transition_depth_to_read(RHICmdBuffer *c, RHITexture t)   { (void)c; (void)t; }
void rhi_cmd_memory_barrier(RHICmdBuffer *c)                            { (void)c; }
void rhi_cmd_dispatch(RHICmdBuffer *c, u32 x, u32 y, u32 z)            { (void)c; (void)x; (void)y; (void)z; }

/* Stage 4 scene editor Phase 2 Task 3: the editor viewport renderer +
 * myui RHI canvas are link-only in test_editor_shell (dummy PAL — no device,
 * never called), so these are pure link satisfiers like the rest. */
void rhi_texture_upload_mip(RHIDevice *d, RHITexture t, u32 mip, u32 w, u32 h,
                            const void *data, usize size) {
    (void)d;
#ifdef BREAK_EDITOR_SHELL_TESTING
    if (g_editor_rhi_fake.enabled) {
        /* mirrors the real backends' checks against the LAST created
         * texture's extent (the preview uploads right after its create) */
        u32 mw = g_editor_rhi_fake.stats.last_texture_w >> mip;
        u32 mh = g_editor_rhi_fake.stats.last_texture_h >> mip;
        if (mw == 0u) mw = 1u;
        if (mh == 0u) mh = 1u;
        if (editor_rhi_fake_texture_live(t) && data != NULL &&
            mip < g_editor_rhi_fake.stats.last_texture_mips && w == mw &&
            h == mh && size >= (usize)w * h * 4u) {
            g_editor_rhi_fake.stats.mip_uploads++;
        } else {
            g_editor_rhi_fake.stats.mip_upload_rejects++;
        }
        return;
    }
#endif
    (void)t; (void)mip; (void)w; (void)h; (void)data; (void)size;
}
void rhi_offscreen_fbo_set_clear_color(RHIDevice *d, RHIOffscreenFBO *fbo,
                                       f32 r, f32 g, f32 b, f32 a) {
    (void)d; (void)fbo; (void)r; (void)g; (void)b; (void)a;
}
void rhi_cmd_clear_depth(RHICmdBuffer *c) { (void)c; }
