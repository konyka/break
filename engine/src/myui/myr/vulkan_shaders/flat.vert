#version 450
/* flat-color triangles: vec2 positions, resolution+color via push constants */
layout(location = 0) in vec2 a_pos;
layout(push_constant) uniform Push {
  vec2 u_resolution;
  vec4 u_color;
} pc;
void main() {
  vec2 ndc = (a_pos / pc.u_resolution) * 2.0 - 1.0;
  gl_Position = vec4(ndc.x, ndc.y, 0.0, 1.0); /* Vulkan NDC: +y is down already (no GL-style flip) */
}
