#version 450
/* textured quads: vec2 pos + vec2 uv */
layout(location = 0) in vec2 a_pos;
layout(location = 1) in vec2 a_uv;
layout(push_constant) uniform Push {
  vec2 u_resolution;
  vec4 u_color;
} pc;
layout(location = 0) out vec2 v_uv;
void main() {
  vec2 ndc = (a_pos / pc.u_resolution) * 2.0 - 1.0;
  gl_Position = vec4(ndc.x, ndc.y, 0.0, 1.0); /* Vulkan NDC: +y is down already (no GL-style flip) */
  v_uv = a_uv;
}
