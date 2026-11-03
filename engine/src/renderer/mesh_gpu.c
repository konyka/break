#include <renderer/mesh_gpu.h>
#include <stdio.h>
#include <string.h>

bool mesh_gpu_upload(RHIDevice *dev, const MeshBuffer *mesh, MeshGpu *out) {
    if (out) {
        out->vertex = RHI_HANDLE_NULL;
        out->index = RHI_HANDLE_NULL;
    }
    if (!dev || !mesh || !out || mesh->count == 0u) return false;
    RHIBufferDesc vertex_desc;
    if (!mesh_buffer_upload_desc(mesh, &vertex_desc)) return false;
    if (!rhi_buffer_desc_validate(&vertex_desc)) return false;
    out->vertex = rhi_buffer_create(dev, &vertex_desc);
    if (!rhi_handle_valid(out->vertex)) {
        out->vertex = RHI_HANDLE_NULL;
        return false;
    }
    if (mesh->index_count == 0u) return true;
    RHIBufferDesc index_desc;
    if (!mesh_buffer_index_desc(mesh, &index_desc) || !rhi_buffer_desc_validate(&index_desc)) {
        rhi_buffer_destroy(dev, out->vertex);
        out->vertex = RHI_HANDLE_NULL;
        return false;
    }
    out->index = rhi_buffer_create(dev, &index_desc);
    if (!rhi_handle_valid(out->index)) {
        rhi_buffer_destroy(dev, out->vertex);
        out->vertex = RHI_HANDLE_NULL;
        out->index = RHI_HANDLE_NULL;
        return false;
    }
    return true;
}

void mesh_gpu_destroy(RHIDevice *dev, MeshGpu *gpu) {
    if (!dev || !gpu) return;
    if (rhi_handle_valid(gpu->index)) rhi_buffer_destroy(dev, gpu->index);
    if (rhi_handle_valid(gpu->vertex)) rhi_buffer_destroy(dev, gpu->vertex);
    gpu->vertex = RHI_HANDLE_NULL;
    gpu->index = RHI_HANDLE_NULL;
}

bool mesh_gpu_draw_desc(RHICmdBuffer *cmd, const MeshGpu *gpu,
                        const MeshDrawDesc *desc, u32 instance_count) {
    if (!cmd || !gpu || !desc || desc->vertex_count == 0u ||
        desc->stride != (u32)sizeof(MeshVertex) || instance_count == 0u ||
        !rhi_handle_valid(gpu->vertex)) return false;
    rhi_cmd_bind_vertex_buffer(cmd, gpu->vertex, 0);
    if (desc->index_count > 0u && rhi_handle_valid(gpu->index)) {
        rhi_cmd_bind_index_buffer(cmd, gpu->index, 0, true);
        rhi_cmd_draw_indexed(cmd, desc->index_count, instance_count);
    } else {
        rhi_cmd_draw(cmd, desc->vertex_count, instance_count);
    }
    return true;
}

bool mesh_gpu_draw(RHICmdBuffer *cmd, const MeshBuffer *mesh, const MeshGpu *gpu) {
    if (!mesh) return false;
    MeshDrawDesc desc;
    return mesh_buffer_draw_desc(mesh, &desc) && mesh_gpu_draw_desc(cmd, gpu, &desc, 1u);
}

static const char MESH_VERT[] =
    "#version 450 core\n"
    "layout(location = 0) in vec3 a_pos;\n"
    "layout(location = 1) in vec3 a_normal;\n"
    "layout(location = 2) in uint a_material;\n"
    "out vec3 v_normal;\n"
    "flat out uint v_material;\n"
    "void main() {\n"
    "    v_normal = a_normal;\n"
    "    v_material = a_material;\n"
    "    gl_Position = vec4(a_pos.x, a_pos.z, 0.0, 1.0);\n"
    "}\n";

static const char MESH_FRAG[] =
    "#version 450 core\n"
    "in vec3 v_normal;\n"
    "flat in uint v_material;\n"
    "layout(location = 0) out vec4 FragColor;\n"
    "void main() {\n"
    "    FragColor = vec4(v_normal.y, float(v_material) / 255.0, 0.0, 1.0);\n"
    "}\n";

bool mesh_pipeline_create(RHIDevice *dev, MeshPipeline *out) {
    if (out) memset(out, 0, sizeof(*out));
    if (!dev || !out) return false;
    out->vert = rhi_shader_create(dev, MESH_VERT, sizeof(MESH_VERT) - 1u, false);
    out->frag = rhi_shader_create(dev, MESH_FRAG, sizeof(MESH_FRAG) - 1u, true);
    if (!rhi_handle_valid(out->vert) || !rhi_handle_valid(out->frag)) {
        mesh_pipeline_destroy(dev, out);
        return false;
    }
    RHIPipelineDesc desc;
    memset(&desc, 0, sizeof(desc));
    desc.vert = out->vert;
    desc.frag = out->frag;
    desc.vertex_stride = (u32)sizeof(MeshVertex);
    desc.mesh_stage_vertex = true;
    desc.disable_culling = true;
    out->pipeline = rhi_pipeline_create(dev, &desc);
    if (!rhi_handle_valid(out->pipeline)) {
        mesh_pipeline_destroy(dev, out);
        return false;
    }
    return true;
}

static const char WORLD_PUSH[] =
    "layout(push_constant) uniform WorldPush {\n"
    "    mat4 u_view;\n"
    "    mat4 u_proj;\n"
    "    vec3 u_sun_dir;\n"
    "    float u_fog;\n"
    "    vec3 u_sun_color;\n"
    "    float u_roughness;\n"
    "    vec3 u_ambient;\n"
    "    int u_instance_offset;\n"
    "    vec3 u_camera_pos;\n"
    "    float _pad0;\n"
    "    vec3 u_base_color;\n"
    "    float _pad1;\n"
    "} pc;\n";

static const char WORLD_VERTEX_BODY[] =
    "layout(location = 0) out vec3 v_normal;\n"
    "layout(location = 1) out vec3 v_world;\n"
    "layout(location = 2) out vec2 v_uv;\n"
    "void main() {\n"
    "    mat4 model = mat4(1.0);\n"
    "%s"
    "    vec4 world = model * vec4(a_pos, 1.0);\n"
    "    v_normal = mat3(model) * a_normal;\n"
    "    v_world = world.xyz;\n"
    "    v_uv = a_uv;\n"
    "    gl_Position = u_proj * u_view * world;\n"
    "%s"
    "}\n";

static const char WORLD_INSTANCE_MAIN[] =
    "    int idx = (gl_InstanceID + u_instance_offset) * 4;\n"
    "    model = mat4(texelFetch(u_instances, idx),\n"
    "                 texelFetch(u_instances, idx + 1),\n"
    "                 texelFetch(u_instances, idx + 2),\n"
    "                 texelFetch(u_instances, idx + 3));\n";

static const char WORLD_FRAGMENT_BODY[] =
    "layout(location = 0) in vec3 v_normal;\n"
    "layout(location = 1) in vec3 v_world;\n"
    "layout(location = 2) in vec2 v_uv;\n"
    "layout(location = 0) out vec4 FragColor;\n"
    "void main() {\n"
    "    vec3 N = normalize(v_normal);\n"
    "    vec3 L = normalize(u_sun_dir);\n"
    "    vec3 V = normalize(u_camera_pos - v_world);\n"
    "    vec3 H = normalize(L + V);\n"
    "    float diff = max(dot(N, L), 0.0);\n"
    "    float spec = pow(max(dot(N, H), 0.0), mix(64.0, 4.0, u_roughness));\n"
    "    spec *= (1.0 - u_roughness) * 0.15;\n"
    "    vec3 albedo = texture(u_albedo, v_uv).rgb * u_base_color;\n"
    "    vec3 color = u_ambient * albedo + u_sun_color * (diff + spec) * albedo;\n"
    "    float fog_amount = clamp(length(u_camera_pos - v_world) * u_fog * 0.05, 0.0, 1.0);\n"
    "    FragColor = vec4(mix(color, u_ambient * 0.5, fog_amount), 1.0);\n"
    "}\n";

static bool world_shader_source(char *out, usize cap, bool fragment,
                                bool vulkan, bool instanced) {
    const char *header =
        "layout(location = 0) in vec3 a_pos;\n"
        "layout(location = 1) in vec3 a_normal;\n"
        "layout(location = 2) in uint a_material;\n"
        "layout(location = 3) in vec2 a_uv;\n";
    int wrote;
    if (fragment) {
        const char *gl_uniforms =
            "uniform vec3 u_sun_dir;\n"
            "uniform float u_fog;\n"
            "uniform vec3 u_sun_color;\n"
            "uniform float u_roughness;\n"
            "uniform vec3 u_ambient;\n"
            "uniform vec3 u_camera_pos;\n"
            "uniform vec3 u_base_color;\n";
        const char *vk_aliases =
            "#define u_sun_dir pc.u_sun_dir\n"
            "#define u_fog pc.u_fog\n"
            "#define u_sun_color pc.u_sun_color\n"
            "#define u_roughness pc.u_roughness\n"
            "#define u_ambient pc.u_ambient\n"
            "#define u_camera_pos pc.u_camera_pos\n"
            "#define u_base_color pc.u_base_color\n";
        wrote = snprintf(out, cap, "#version 450 core\n%s%s%s%s%s",
                         vulkan ? WORLD_PUSH : gl_uniforms,
                         vulkan ? vk_aliases : "",
                         vulkan ? "layout(binding = 0) uniform sampler2D u_albedo;\n"
                                : "layout(binding = 0) uniform sampler2D u_albedo;\n",
                         "", WORLD_FRAGMENT_BODY);
    } else {
        const char *gl_uniforms =
            "uniform mat4 u_view;\n"
            "uniform mat4 u_proj;\n"
            "uniform int u_instance_offset;\n";
        const char *vk_aliases =
            "#define u_view pc.u_view\n"
            "#define u_proj pc.u_proj\n"
            "#define u_instance_offset pc.u_instance_offset\n"
            "#define gl_InstanceID gl_InstanceIndex\n";
        const char *instance_decl = instanced
            ? (vulkan ? "layout(set = 1, binding = 0) uniform samplerBuffer u_instances;\n"
                      : "layout(binding = 5) uniform samplerBuffer u_instances;\n")
            : "";
        char body[4096];
        int body_written = snprintf(body, sizeof(body), WORLD_VERTEX_BODY,
                                    instanced ? WORLD_INSTANCE_MAIN : "",
                                    vulkan ? "    gl_Position.z = (gl_Position.z + gl_Position.w) * 0.5;\n" : "");
        if (body_written < 0 || (usize)body_written >= sizeof(body)) return false;
        wrote = snprintf(out, cap, "#version 450 core\n%s%s%s%s%s",
                         header, vulkan ? WORLD_PUSH : gl_uniforms,
                         vulkan ? vk_aliases : "", instance_decl, body);
    }
    return wrote > 0 && (usize)wrote < cap;
}

bool mesh_pipeline_create_lit(RHIDevice *dev, MeshPipeline *out, bool instanced) {
    if (out) memset(out, 0, sizeof(*out));
    if (!dev || !out) return false;
    RHICapabilities caps;
    if (!rhi_device_get_capabilities(dev, &caps)) return false;
    bool vulkan = caps.shader_variant == RHI_SHADER_VARIANT_GLSL_VK;
    char vert_source[8192];
    char frag_source[8192];
    if (!world_shader_source(vert_source, sizeof(vert_source), false, vulkan, instanced) ||
        !world_shader_source(frag_source, sizeof(frag_source), true, vulkan, instanced)) return false;
    out->vert = rhi_shader_create(dev, vert_source, strlen(vert_source), false);
    out->frag = rhi_shader_create(dev, frag_source, strlen(frag_source), true);
    if (!rhi_handle_valid(out->vert) || !rhi_handle_valid(out->frag)) {
        mesh_pipeline_destroy(dev, out);
        return false;
    }
    RHIPipelineDesc desc;
    memset(&desc, 0, sizeof(desc));
    desc.vert = out->vert;
    desc.frag = out->frag;
    desc.vertex_stride = (u32)sizeof(MeshVertex);
    desc.mesh_stage_vertex = true;
    desc.uses_textures = true;
    desc.disable_culling = true;
    desc.is_instanced = instanced;
    desc.uses_texel_buffer = instanced;
    out->pipeline = rhi_pipeline_create(dev, &desc);
    if (!rhi_handle_valid(out->pipeline)) {
        mesh_pipeline_destroy(dev, out);
        return false;
    }
    out->bindings = rhi_pipeline_bindings_create(dev, out->pipeline);
    if (!out->bindings) {
        mesh_pipeline_destroy(dev, out);
        return false;
    }
#define RESOLVE(field, name) out->field = rhi_pipeline_bindings_resolve(out->bindings, name)
    RESOLVE(loc_view, "u_view");
    RESOLVE(loc_proj, "u_proj");
    RESOLVE(loc_sun_dir, "u_sun_dir");
    RESOLVE(loc_sun_color, "u_sun_color");
    RESOLVE(loc_ambient, "u_ambient");
    RESOLVE(loc_fog, "u_fog");
    RESOLVE(loc_camera, "u_camera_pos");
    RESOLVE(loc_base_color, "u_base_color");
    RESOLVE(loc_roughness, "u_roughness");
    RESOLVE(loc_albedo, "u_albedo");
    RESOLVE(loc_instance_offset, "u_instance_offset");
#undef RESOLVE
    if (out->loc_view < 0 || out->loc_proj < 0 || out->loc_sun_dir < 0 ||
        out->loc_sun_color < 0 || out->loc_ambient < 0 || out->loc_fog < 0 ||
        out->loc_camera < 0 || out->loc_base_color < 0 || out->loc_roughness < 0 ||
        (instanced && out->loc_instance_offset < 0)) {
        mesh_pipeline_destroy(dev, out);
        return false;
    }
    out->lit = true;
    out->instanced = instanced;
    return true;
}

void mesh_pipeline_bind_frame(RHICmdBuffer *cmd, const MeshPipeline *pipe,
                              const Mat4 *view, const Mat4 *projection,
                              const TimeOfDayLighting *lighting, Vec3 camera) {
    if (!cmd || !pipe || !pipe->lit || !view || !projection || !lighting) return;
    rhi_cmd_set_uniform_mat4(cmd, pipe->loc_view, &view->e[0][0]);
    rhi_cmd_set_uniform_mat4(cmd, pipe->loc_proj, &projection->e[0][0]);
    rhi_cmd_set_uniform_vec3(cmd, pipe->loc_sun_dir,
                             lighting->sun_dir.e[0], lighting->sun_dir.e[1], lighting->sun_dir.e[2]);
    rhi_cmd_set_uniform_vec3(cmd, pipe->loc_sun_color,
                             lighting->sun_color.e[0], lighting->sun_color.e[1], lighting->sun_color.e[2]);
    rhi_cmd_set_uniform_vec3(cmd, pipe->loc_ambient,
                             lighting->ambient.e[0], lighting->ambient.e[1], lighting->ambient.e[2]);
    rhi_cmd_set_uniform_f32(cmd, pipe->loc_fog, lighting->fog);
    rhi_cmd_set_uniform_vec3(cmd, pipe->loc_camera, camera.e[0], camera.e[1], camera.e[2]);
}

void mesh_pipeline_bind_material(RHICmdBuffer *cmd, const MeshPipeline *pipe,
                                 const MeshMaterial *material,
                                 RHITexture white, RHISampler fallback) {
    if (!cmd || !pipe || !pipe->lit || !material) return;
    RHITexture texture = material->albedo;
    RHISampler sampler = material->sampler;
    if (!rhi_handle_valid(texture) || !rhi_handle_valid(sampler)) {
        texture = white;
        sampler = fallback;
    }
    rhi_cmd_set_uniform_vec3(cmd, pipe->loc_base_color,
                             material->base_color.e[0], material->base_color.e[1], material->base_color.e[2]);
    rhi_cmd_set_uniform_f32(cmd, pipe->loc_roughness, material->roughness);
    if (pipe->loc_albedo >= 0) rhi_cmd_set_uniform_i32(cmd, pipe->loc_albedo, 0);
    rhi_cmd_bind_texture(cmd, texture, sampler, 0u);
}

void mesh_pipeline_set_instance_offset(RHICmdBuffer *cmd, const MeshPipeline *pipe,
                                       u32 first_instance) {
    if (!cmd || !pipe || !pipe->lit || !pipe->instanced || first_instance > (u32)INT32_MAX) return;
    rhi_cmd_set_uniform_i32(cmd, pipe->loc_instance_offset, (i32)first_instance);
}

void mesh_pipeline_destroy(RHIDevice *dev, MeshPipeline *pipe) {
    if (!dev || !pipe) return;
    if (pipe->bindings) rhi_pipeline_bindings_destroy(dev, pipe->bindings);
    if (rhi_handle_valid(pipe->pipeline)) rhi_pipeline_destroy(dev, pipe->pipeline);
    if (rhi_handle_valid(pipe->frag)) rhi_shader_destroy(dev, pipe->frag);
    if (rhi_handle_valid(pipe->vert)) rhi_shader_destroy(dev, pipe->vert);
    memset(pipe, 0, sizeof(*pipe));
}

bool mesh_gpu_draw_with_pipeline(RHICmdBuffer *cmd, const MeshPipeline *pipe,
                                 const MeshBuffer *mesh, const MeshGpu *gpu) {
    if (!cmd || !pipe || !rhi_handle_valid(pipe->pipeline)) return false;
    rhi_cmd_bind_pipeline(cmd, pipe->pipeline);
    return mesh_gpu_draw(cmd, mesh, gpu);
}
