# Phase 5B: Clustered Forward Lighting

## Architecture Decision

**Approach**: CPU-clustered forward with texture buffer (TBO) for light data.

### Why not simpler multi-light?
- Push constants max 256 bytes — already using 252 (3×mat4 + 4×vec3)
- No room for light arrays in push constants
- Need a separate data channel for light data

### Why not SSBO?
- Would require new RHI resource type (storage buffer)
- TBO (texture buffer) already works through existing texture infrastructure
- GL: `samplerBuffer` + `GL_TEXTURE_BUFFER`
- VK: `VK_BUFFER_USAGE_UNIFORM_TEXEL_BUFFER_BIT` + `vkCmdBindDescriptorSets`
- Both map to existing descriptor set binding in Vulkan

### Why not GPU compute culling?
- No compute shader RHI support yet
- CPU culling viable for ≤256 lights on integrated GPU
- CPU overhead predictable, no dispatch latency

## Data Flow

```
CPU per frame:
  1. Update light positions/colors into light buffer (host-visible)
  2. For each cluster (16×8×24 = 3072):
     - Test each point light against cluster AABB
     - Write light indices into light grid
  3. Upload light grid to GPU

GPU per fragment:
  1. Compute cluster index from gl_FragCoord + linear depth
  2. Read light grid[cluster] → (offset, count)
  3. Iterate count lights from light index list
  4. Accumulate Blinn-Phong for each light
```

## Cluster Grid Configuration

```
CLUSTER_X = 16
CLUSTER_Y = 8  
CLUSTER_Z = 24
Total clusters = 3072
Max lights per cluster = 128
Max point lights = 256
Max directional lights = 4
```

Z-slice distribution: exponential (more slices near camera for higher density)

## New RHI API

```c
// New buffer usage flag
RHI_BUFFER_USAGE_TEXEL = 0x08

// Bind both light data + light grid texel buffers in one descriptor set
void rhi_cmd_bind_texel_buffers(RHICmdBuffer *cmd, RHIBuffer buf0, RHIBuffer buf1);
```

## Shader Changes

### Vertex shader (minimal change)
- Keep push constants for model/view/proj/camera_pos
- Remove light_dir/light_color/ambient from push constants
- Pass world pos, normal, UV to fragment

### Fragment shader (major change)
- Push constants: only model, view, proj, camera_pos (144 bytes — lots of room)
- Binding 0: albedo texture (existing)
- Binding 1: light data texel buffer (all lights packed)
- Binding 2: light grid texel buffer (per-cluster offset+count + light indices)
- Uniforms: cluster dimensions, near/far, screen size (push constants)
- Loop over lights per cluster, accumulate Blinn-Phong

## Files to Create/Modify

### New files:
- `src/renderer/lighting.c/h` — light system, cluster culling
- `shaders/blinn_phong_clustered_vk.vert/frag` — new Vulkan shaders  
- `shaders/blinn_phong_clustered.vert/frag` — new GL shaders

### Modified files:
- `src/rhi/rhi.h` — add `RHI_BUFFER_USAGE_TEXEL`, `rhi_cmd_bind_texel_buffer`
- `src/rhi/rhi_gl.c` — implement TBO binding
- `src/rhi/rhi_vk.c` — implement texel buffer descriptor set
- `src/main.c` — integrate lighting system

## Implementation Order

1. RHI: Add texel buffer support to both backends
2. Renderer: Light system with cluster culling (CPU)
3. Shaders: Clustered Blinn-Phong (GL + Vulkan)
4. Test: Verify on both backends with 256 point lights
5. Stress test: 1000 draws + 256 lights

## Performance Targets

- 256 point lights at 60+ FPS on Intel UHD
- CPU culling overhead < 1ms per frame
- No validation errors on Vulkan

## Results — COMPLETED

- Vulkan: ~245 FPS with 32 orbiting point lights, zero validation errors
- OpenGL: ~269 FPS with 32 orbiting point lights
- test_vulkan: ALL PASSED (500-frame + 1000-draw stress tests)
- Pipeline-aware push constant offsets via `uses_texel_buffer` flag in `VKPipelineData`
- Vulkan: texel buffers bound as set 1 (bindings 0-1) via dedicated `texel_layout`
- OpenGL: TBO textures on units 1-2, `samplerBuffer` in GLSL
