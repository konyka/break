# D3D12 blinn_phong HLSL Sidecar Implementation Plan

> **For agentic workers:** REQUIRED SUB-SKILL: Use superpowers:subagent-driven-development (recommended) or superpowers:executing-plans to implement this plan task-by-task. Steps use checkbox (`- [ ]`) syntax for tracking.

**Goal:** Hand-author the first real renderer pipeline HLSL sidecar pair for D3D12 and prove it compiles, binds uniforms at the engine's expected byte offsets, samples a bound texture, and renders a verifiable result.

**Architecture:** `blinn_phong_hlsl.{vert,frag}` are hand-written HLSL twins of the existing GLSL `blinn_phong.{vert,frag}`, following the convention the `blit`/`myui` sidecars already use. The engine resolves uniform names through `rhi_pipeline_bindings_resolve`, which on D3D12 reads `// rhi:uniform <name> <byte offset>` markers in the sidecar source; the sidecar therefore owns the byte offsets, and the vertex/fragment root-constant struct layout must match those offsets exactly.

**Tech Stack:** C11, HLSL (SM 6.0, dxc), D3D12 Agility SDK, WARP runtime tests, CMake dxc step.

## Global Constraints

- The sidecar must reproduce the GLSL `blinn_phong` semantics exactly: world position from `u_model`, `u_proj * u_view * world`, normalized normal, `L = -u_light_dir`, Blinn-Phong specular with `spec^8` scaled by 0.15, and `color = albedo * (u_ambient + u_light_color * diff) + u_light_color * spec * 0.15`.
- The D3D12 push-constant range is 256 bytes for graphics. The seven engine-resolved uniforms must fit exactly:
  `u_model` @ 0 (float4x4, 64B), `u_view` @ 64, `u_proj` @ 128, `u_light_dir` @ 192 (float3, 16B slot), `u_light_color` @ 208, `u_ambient` @ 224, `u_camera_pos` @ 240. Total 256 bytes.
- The vertex input layout must match the GLSL pipeline: `aPos` float3 @ 0, `aNormal` float3 @ 12, `aUV` float2 @ 24, stride 32 bytes.
- `u_albedo` is a texture sampled at `register(t0, space0)`; the sampler is a `SamplerState` at `register(s0, space0)`.
- Do not change the engine's forward path, the material binders, or any other backend in this plan.
- Verify with WARP pixels, not handle existence alone.
- Do not commit generated DXIL, build outputs, or scratch files.

---

### Task 1: Author the blinn_phong HLSL Sidecar Pair

**Files:**
- Create: `engine/shaders/blinn_phong_hlsl.vert`
- Create: `engine/shaders/blinn_phong_hlsl.frag`
- Modify: `engine/CMakeLists.txt` (add `blinn_phong` to `ENGINE_D3D12_HLSL_PIPELINES`)

**Interfaces:**
- Consumes: the GLSL originals `engine/shaders/blinn_phong.vert` and `blinn_phong.frag`; the sidecar conventions in `engine/shaders/blit_hlsl.{vert,frag}` and `myui_hlsl.{vert,frag}`.
- Produces: a D3D12-compilable sidecar pair whose `// rhi:uniform` markers publish the seven engine-resolved uniform names at the byte offsets listed in Global Constraints.

- [ ] **Step 1: Write the vertex sidecar**

Declare one root-constant struct holding all seven members at the offsets from Global Constraints, so the byte layout is identical in both stages. The vertex shader reads `u_model`, `u_view`, `u_proj` and outputs world position, normal and UV. The three matrix markers belong in this file.

- [ ] **Step 2: Write the fragment sidecar**

Same struct declaration. The fragment shader samples `register(t0)` with the static sampler at `register(s0)`, computes the lighting exactly as the GLSL does, and outputs the color. The four lighting/camera markers belong in this file.

- [ ] **Step 3: Register the pipeline in the CMake sidecar contract**

Add `blinn_phong` to `ENGINE_D3D12_HLSL_PIPELINES` so a missing sidecar fails the configure step instead of surfacing later as a runtime failure.

- [ ] **Step 4: Build and confirm the DXIL artifacts exist**

Run:
```bash
cd E:/work/break/build-d3d12-debug
cmake . && ninja
ls shaders_d3d12/blinn_phong_hlsl.*
```

Expected: `blinn_phong_hlsl.vert.dxil` and `blinn_phong_hlsl.frag.dxil` are produced with no dxc errors.

---

### Task 2: Prove the Sidecar Renders on D3D12

**Files:**
- Modify: `engine/tests/test_d3d12_warp_runtime.c`

**Interfaces:**
- Consumes: `rhi_shader_create_path`, `rhi_pipeline_get_uniform_location`, `rhi_cmd_push_constants`, `rhi_cmd_bind_texture`, the existing offscreen FBO and texture readback helpers.
- Produces: a WARP test proving the sidecar compiles, the uniform markers resolve to the expected byte offsets, and the shaded output matches the GLSL formula.

- [ ] **Step 1: Write the test**

Create a test that:
1. Resolves both shaders through `rhi_shader_create_path` with the GLSL-style paths `shaders/blinn_phong.vert` and `shaders/blinn_phong.frag`.
2. Builds a pipeline with `vertex_stride = 32` and `RHI_FORMAT_R8G8B8A8_UNORM`.
3. Asserts `rhi_pipeline_get_uniform_location` returns 0, 64, 128, 192, 208, 224, 240 for `u_model`, `u_view`, `u_proj`, `u_light_dir`, `u_light_color`, `u_ambient`, `u_camera_pos`.
4. Creates a 2x2 red texture and a triangle with position, normal and UV.
5. Pushes identity model/view/proj, `u_light_dir` = (0,0,-1), `u_light_color` = (0,0,0), `u_ambient` = (1,1,1), `u_camera_pos` = (0,0,0).
6. Binds the red texture at unit 0, draws into an 8x8 offscreen FBO, reads back, and asserts every pixel is red.

With `u_light_color` zero the diffuse and specular terms vanish, so the expected color is exactly the albedo - deterministic and independent of the normal.

- [ ] **Step 2: Run it and confirm it fails before the sidecar exists**

Run:
```bash
cd E:/work/break/build-d3d12-debug
ninja test_d3d12_warp_runtime
ctest -R test_d3d12_warp_runtime -V
```

Expected before Task 1: the pipeline cannot be created or the uniform markers do not resolve.

- [ ] **Step 3: Make it pass**

Implement only what the test needs on top of Task 1.

- [ ] **Step 4: Reverse validation**

Change one expected channel so the assertion must fail, confirm the test turns red, restore, and confirm green.

- [ ] **Step 5: Run the specialist suites**

Run:
```bash
cd E:/work/break/build-d3d12-debug
ctest -R "d3d12|warp|swapchain" --output-on-failure
cd ../build-gl && ctest -LE graphics --output-on-failure
cd ../build-vk && ctest -LE graphics --output-on-failure
```

Expected: D3D12 specialist tests pass; GL and Vulkan unchanged.

---

### Task 3: Document and Commit

**Files:**
- Modify: `docs/Implementation_Status.md`

**Interfaces:**
- Consumes: the verified sidecar and its pixel evidence.
- Produces: documented sidecar layout, evidence, and the remaining ordered work.

- [ ] **Step 1: Document**

Record the sidecar layout and byte offsets, the CMake sidecar contract, the WARP pixel proof and reverse validation, and the remaining order: material binders, then shadow map, then compute bindings, then the engine call-site migration to the path API.

- [ ] **Step 2: Check and commit**

Run `git diff --check`, stage only source, tests, docs and the plan, then commit and push.
