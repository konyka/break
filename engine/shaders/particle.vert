#version 450

struct Particle {
    vec4 pos_life;
    vec4 vel_maxlife;
    vec4 size_color;
    vec4 previous_pos;
};

/* Vulkan supplies view/proj via a push-constant block; desktop GL uses loose
 * uniforms. Alive particles are indexed through DrawBuf (Round 12 GPU cull).
 * R167: DrawBuf uses DrawIndirectCommand header; instanceCount drives draw. */
#ifdef VULKAN
layout(std430, set = 0, binding = 0) readonly buffer ParticleBuf {
    Particle particles[];
};
layout(std430, set = 0, binding = 1) readonly buffer DrawBuf {
    uint vertexCount;
    uint instanceCount;
    uint firstVertex;
    uint firstInstance;
    uint indices[];
};
layout(push_constant) uniform Push {
    mat4 view;
    mat4 proj;
} push;
#define P_VIEW  push.view
#define P_PROJ  push.proj
#define P_INST  gl_InstanceIndex
#else
layout(std430, binding = 0) readonly buffer ParticleBuf {
    Particle particles[];
};
layout(std430, binding = 1) readonly buffer DrawBuf {
    uint vertexCount;
    uint instanceCount;
    uint firstVertex;
    uint firstInstance;
    uint indices[];
};
uniform mat4 u_view;
uniform mat4 u_proj;
#define P_VIEW  u_view
#define P_PROJ  u_proj
#define P_INST  gl_InstanceID
#endif

#ifdef FORWARD_MRT
#ifdef VULKAN
layout(std140, set = 1, binding = 0) uniform ForwardTemporal {
#else
layout(std140, binding = 0) uniform ForwardTemporal {
#endif
    mat4 u_prev_vp;
    mat4 u_prev_model_unused;
} temporal;
#endif

layout(location = 0) out vec4 v_color;
layout(location = 1) out float v_size;
#ifdef FORWARD_MRT
layout(location = 2) out vec2 v_velocity;
#endif

void main() {
    /* R167: draw_indirect already limits instances to alive count; keep a
     * defensive bound for the non-cull fallback path. */
    if (P_INST >= instanceCount) {
        gl_Position = vec4(0.0);
        gl_PointSize = 0.0;
        v_color = vec4(0.0);
        v_size = 0.0;
#ifdef FORWARD_MRT
        v_velocity = vec2(0.0);
#endif
        return;
    }

    uint idx = indices[P_INST];
    if (idx >= particles.length()) {
        gl_Position = vec4(0.0);
        gl_PointSize = 0.0;
        v_color = vec4(0.0);
        v_size = 0.0;
#ifdef FORWARD_MRT
        v_velocity = vec2(0.0);
#endif
        return;
    }

    Particle p = particles[idx];
    float life = p.pos_life.w;

    if (life <= 0.0) {
        gl_Position = vec4(0.0);
        gl_PointSize = 0.0;
        v_color = vec4(0.0);
        v_size = 0.0;
#ifdef FORWARD_MRT
        v_velocity = vec2(0.0);
#endif
        return;
    }

    vec3 pos = p.pos_life.xyz;
    float size = p.size_color.x;
    float alpha = p.size_color.w;
    vec3 color = p.size_color.yzw;

    vec4 current_clip = P_PROJ * P_VIEW * vec4(pos, 1.0);
    gl_Position = current_clip;
#ifdef VULKAN
    /* R214-A: OpenGL proj → Vulkan clip.z [0,1]. */
    gl_Position.z = (gl_Position.z + gl_Position.w) * 0.5;
#endif
    gl_PointSize = max(1.0, size * 400.0 / gl_Position.w);
    v_color = vec4(color * alpha, alpha);
    v_size = size;
#ifdef FORWARD_MRT
    vec4 previous_clip = temporal.u_prev_vp * vec4(p.previous_pos.xyz, 1.0);
    v_velocity = current_clip.xy / current_clip.w - previous_clip.xy / previous_clip.w;
#endif
}
