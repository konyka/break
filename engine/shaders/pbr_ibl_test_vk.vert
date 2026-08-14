#version 450 core

/* TEST 7 uses a standalone vertex contract. The production clustered Vulkan
 * pair has compact, stage-specific push layouts; this smoke test only needs a
 * clip-space triangle so its pixel gate isolates IBL descriptor sampling. */
layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aNormal;
layout(location = 2) in vec2 aUV;
layout(location = 0) out vec3 vWorldPos;
layout(location = 1) out vec3 vNormal;
layout(location = 2) out vec2 vUV;

void main() {
    vWorldPos = aPos;
    vNormal = aNormal;
    vUV = aUV;
    gl_Position = vec4(aPos, 1.0);
}
