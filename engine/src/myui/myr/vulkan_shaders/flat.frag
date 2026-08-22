#version 450
layout(push_constant) uniform Push {
  vec2 u_resolution;
  vec4 u_color;
} pc;
layout(location = 0) out vec4 out_color;
void main() {
  out_color = pc.u_color;
}
