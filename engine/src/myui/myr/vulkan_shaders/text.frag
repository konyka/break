#version 450
/* glyph quads: R8 alpha texture tinted with the push-constant color */
layout(push_constant) uniform Push {
  vec2 u_resolution;
  vec4 u_color;
} pc;
layout(set = 0, binding = 0) uniform sampler2D u_tex;
layout(location = 0) in vec2 v_uv;
layout(location = 0) out vec4 out_color;
void main() {
  out_color = vec4(pc.u_color.rgb, pc.u_color.a * texture(u_tex, v_uv).r);
}
