#version 450

struct Particle {
    vec4 pos_life;
    vec4 vel_maxlife;
    vec4 size_color;
};

layout(std430, binding = 0) readonly buffer ParticleBuf {
    Particle particles[];
};

layout(push_constant) uniform Push {
    mat4 view;
    mat4 proj;
} push;

layout(location = 0) out vec4 v_color;
layout(location = 1) out float v_size;

void main() {
    uint idx = gl_VertexIndex;
    if (idx >= particles.length()) {
        gl_Position = vec4(0.0);
        gl_PointSize = 0.0;
        v_color = vec4(0.0);
        v_size = 0.0;
        return;
    }

    Particle p = particles[idx];
    float life = p.pos_life.w;

    if (life <= 0.0) {
        gl_Position = vec4(0.0);
        gl_PointSize = 0.0;
        v_color = vec4(0.0);
        v_size = 0.0;
        return;
    }

    vec3 pos = p.pos_life.xyz;
    float size = p.size_color.x;
    float alpha = p.size_color.w;
    vec3 color = p.size_color.yzw;

    gl_Position = push.proj * push.view * vec4(pos, 1.0);
    gl_PointSize = max(1.0, size * 400.0 / gl_Position.w);
    v_color = vec4(color * alpha, alpha);
    v_size = size;
}
