// depth_only_hlsl.vert - depth-only VS (D3D12 hand-authored sidecar).
//
// Twin of shaders/depth_only.vert -- but NOT of its GL arm. That file is
// shared between backends behind #ifdef VULKAN, and the two arms differ:
//
//   GL arm      clip.z is left alone; OpenGL's NDC is [-1,1] and the depth
//               range maps it to [0,1] in fixed-function.
//   VULKAN arm  gl_Position.z = (z + w) * 0.5, because Vulkan's NDC is [0,1].
//
// D3D12's NDC is [0,1], same as Vulkan, so this file follows the VULKAN arm.
// The CPU side settles it independently: mat4_ortho() in src/math/math.c
// writes m.e[2][2] = -2/(far-near), the OpenGL form, so u_light_vp leaves the
// CPU producing z in [-1,1] on every backend. Whatever consumes it has to
// convert. Skipping the conversion here would make every cascade render with
// a mirrored depth ramp: shadows would appear on the wrong side of the
// receivers and still look plausible on flat ground, which is the worst
// possible failure shape.
//
// This is the one place in the sidecar set where "mirror the GL variant"
// is the wrong rule, so it is called out rather than left as a comment that
// says "same as GLSL".
//
// No fragment stage: main.c builds this pipeline with is_shadow_depth, which
// drops every render target, and an empty GLSL main() is the GLSL arm's way
// of saying the same thing. A depth-only PSO with frag = RHI_HANDLE_NULL is
// what the shadow-atlas test already builds.
struct PushConsts {
    float4x4 u_model;     //   0
    float4x4 u_light_vp;  //  64
};
ConstantBuffer<PushConsts> g_push : register(b0, space0);
// rhi:uniform u_model 0
// rhi:uniform u_light_vp 64

struct VSOut { float4 pos : SV_Position; };
VSOut main(float3 pos : POSITION) {
    VSOut o;
    o.pos = mul(g_push.u_light_vp, mul(g_push.u_model, float4(pos, 1.0f)));
    // GLSL VULKAN arm: gl_Position.z = (gl_Position.z + gl_Position.w) * 0.5;
    o.pos.z = (o.pos.z + o.pos.w) * 0.5f;
    return o;
}
