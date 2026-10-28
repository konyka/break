# D3D12 blinn_phong HLSL Sidecar Implementation Plan

> **For agentic workers:** REQUIRED SUB-SKILL: Use superpowers:subagent-driven-development (recommended) or superpowers:executing-plans to implement this plan task-by-task. Steps use checkbox (`- [ ]`) syntax for tracking.

**Goal:** Hand-author the first real renderer pipeline HLSL sidecar pair for D3D12 and prove it compiles, binds uniforms at the engine's expected byte offsets, samples a bound texture, and renders a verifiable result.

**Architecture:** `blinn_phong_hlsl.{vert,frag}` are hand-written HLSL twins of the existing GLSL `blinn_phong.{vert,frag}`, following the convention the `blit`/`myui` sidecars already use. The engine resolves uniform names through `rhi_pipeline_bindings_resolve`, which on D3D12 reads `// rhi:uniform <name> <byte offset>` markers in the sidecar source; the sidecar therefore owns the byte offsets, and the vertex/fragment root-constant struct layout must match those offsets exactly.

**Tech Stack:** C11, HLSL (SM 6.0, dxc), D3D12 Agility SDK, WARP runtime tests, CMake dxc step.

## Global Constraints

- The sidecar must reproduce the GLSL `blinn_phong` semantics exactly: world position from `u_model`, `u_proj * u_view * world`, normalized normal, `L = -u_light_dir`, Blinn-Phong specular scaled by 0.15, and `color = albedo * (u_ambient + u_light_color * diff) + u_light_color * spec * 0.15`.
  **Corrected 2026-10-18:** this line originally read `spec^8`. The GLSL at `engine/shaders/blinn_phong.frag:29` is `spec *= spec;` five times, i.e. exponent 2^5 = **32**, not 8. The sidecar implements the GLSL's five squarings. If exponent 8 was ever the intent, that is a pre-existing cross-backend bug in the GLSL itself (VK/GL render it too) and a separate decision — not something a D3D12 sidecar may diverge on.
- The D3D12 push-constant range for graphics is **252 bytes on this pipeline, not the nominal 256**. `rhi_d3d12_root_signature_create` clamps the constants param against the D3D12 root-signature budget of 64 DWORDs, charging one DWORD per descriptor table (`rhi_d3d12.c:2559-2562`); `blinn_phong` declares one SRV table (t0) while its `SamplerState` becomes a static sampler and costs no table, so 64 requested DWORDs clamp to **63 DWORDs = 252 bytes**.
  The seven engine-resolved uniforms fit inside it:
  `u_model` @ 0 (float4x4, 64B), `u_view` @ 64, `u_proj` @ 128, `u_light_dir` @ 192 (float3, 16B slot), `u_light_color` @ 208, `u_ambient` @ 224, `u_camera_pos` @ 240.
  **Consequence:** all uniforms must be written with the 12-byte/64-byte setters. A padded 16-byte write at offset 240 ends at 256, fails `rhi_push_helper_range_ok`, and is dropped with a warning — see Task 2 Step 1 for the test-side rule and Task 2 Step 4 for the negative control.

  **Corrected 2026-10-18 (second correction).** An earlier revision of this note asserted that the HLSL cbuffer "compiles to exactly 252 bytes, so the root signature and the shader agree exactly". Checked against the compiled DXIL rather than assumed, that is not what the shader does:

  - The HLSL struct is **256 bytes** (3 × float4x4 = 192, plus four `float3` in 16-byte slots ending at 256). It cannot be 252 — the last `float3` occupies a 16-byte slot.
  - The fragment stage emits `cbufferLoadLegacy` at slot indices 12, 13, 14, 15. Each returns `CBufRet.f32 = {float,float,float,float}`, so one load covers 4 DWORDs and slot *n* spans bytes `16n .. 16n+15`. Slots 12-15 land on bytes 192 / 208 / 224 / 240, which independently confirms the four published offsets; the last load therefore **spans bytes 240-255** and nominally needs 64 DWORDs.
  - Only components 0, 1 and 2 of that last load are ever extracted (`extractvalue ..., 3` occurs zero times). Component 3 is the `float3` padding lane.

  So the root signature is **4 bytes short of the span the last load nominally covers** — they do not agree exactly. It is harmless today: the unused lane is discarded, and D3D12 defines out-of-range root-constant reads as returning 0. The accurate statement is *the root signature covers every byte the shader actually consumes (0-251), while the compiled load for the last slot nominally spans 240-255.* A future change that starts reading that lane, or that pushes a real eighth uniform past byte 252, breaks this.
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

- [x] **Step 1: Write the vertex sidecar**

Declare one root-constant struct holding all seven members at the offsets from Global Constraints, so the byte layout is identical in both stages. The vertex shader reads `u_model`, `u_view`, `u_proj` and outputs world position, normal and UV. The three matrix markers belong in this file.

- [x] **Step 2: Write the fragment sidecar**

Same struct declaration. The fragment shader samples `register(t0)` with the static sampler at `register(s0)`, computes the lighting exactly as the GLSL does, and outputs the color. The four lighting/camera markers belong in this file.

- [x] **Step 3: Register the pipeline in the CMake sidecar contract**

Add `blinn_phong` to `ENGINE_D3D12_HLSL_PIPELINES` so a missing sidecar fails the configure step instead of surfacing later as a runtime failure.

- [x] **Step 4: Build and confirm the DXIL artifacts exist**

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

- [x] **Step 1: Write the test**

Create a test that:
1. Resolves both shaders through `rhi_shader_create_path` with the GLSL-style paths `shaders/blinn_phong.vert` and `shaders/blinn_phong.frag`.
2. Builds a pipeline with `vertex_stride = 32` and `RHI_FORMAT_R8G8B8A8_UNORM`.
3. Asserts `rhi_pipeline_get_uniform_location` returns 0, 64, 128, 192, 208, 224, 240 for `u_model`, `u_view`, `u_proj`, `u_light_dir`, `u_light_color`, `u_ambient`, `u_camera_pos`.
4. Creates a 2x2 red texture and a triangle with position, normal and UV, authored in NDC so it covers the whole 8x8 target, with every vertex normal `(0,0,1)` and every vertex at world z = 0.
5. Pushes identity model/view/proj, `u_light_dir` = **(0,-1,0)**, `u_light_color` = **(1,1,1)**, `u_ambient` = (1,1,1), `u_camera_pos` = **(0,0,-10)** — all through `rhi_cmd_set_uniform_mat4` (64 B) and `rhi_cmd_set_uniform_vec3` (12 B).
6. Binds the red texture at unit 0, draws into an 8x8 offscreen FBO, reads back, and asserts every pixel is red.

**Corrected 2026-10-18:** this list originally read `u_light_dir` = (0,0,-1), `u_light_color` = (0,0,0), `u_camera_pos` = (0,0,0). Those values make the test fail, for two independent NaN reasons, and the rationale paragraph that followed ("with `u_light_color` zero the diffuse and specular terms vanish") was wrong in a way that hid both:

- `u_camera_pos` = (0,0,0) with a z = 0 triangle puts the camera exactly on the geometry, so `V = normalize(u_camera_pos - world)` is `normalize(0)` = NaN.
- `u_light_dir` = (0,0,-1) gives `L = (0,0,1)`, and the viewport-*centre* pixel is world `(0,0,0)`, where `V` is exactly `(0,0,-1)` and therefore `L + V = 0` → `H = normalize(0)` = NaN.

NaN survives multiplication, and `u_light_color * NaN` is NaN **even when `u_light_color` is zero** — so a zero light colour does not rescue a degenerate `H`. That is exactly why the original design is unsafe.

The corrected values make both lighting terms zero **by geometry**, so nothing depends on a zero multiplier:

- `N = (0,0,1)` on every vertex interpolates constant; `diff = max(dot(N,L),0) = max(dot((0,0,1),(0,1,0)),0) = 0`.
- With `u_camera_pos = (0,0,-10)` and the triangle on z = 0, `V.z = -10/len < 0` strictly, so `V` is never zero-length and `(L+V).z < 0`, so `H` is finite at **every** pixel and `spec = max(dot(N,H),0) = 0`.
- The expected colour is therefore exactly `albedo * u_ambient`, and `u_light_color` is deliberately left **non-zero** at (1,1,1): if the specular term were ever reachable here the colour would shift and the test would turn red, as it would for a mis-resolved `u_light_dir`.

- [x] **Step 2: Run it and confirm it fails before the sidecar exists**

Run:
```bash
cd E:/work/break/build-d3d12-debug
ninja test_d3d12_warp_runtime
ctest -R test_d3d12_warp_runtime -V
```

Expected before Task 1: the pipeline cannot be created or the uniform markers do not resolve.

- [x] **Step 3: Make it pass**

Implement only what the test needs on top of Task 1.

- [x] **Step 4: Reverse validation**

Change one expected channel so the assertion must fail, confirm the test turns red, restore, and confirm green.

- [x] **Step 5: Run the specialist suites**

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

- [x] **Step 1: Document**

Record the sidecar layout and byte offsets, the CMake sidecar contract, the WARP pixel proof and reverse validation, and the remaining order: material binders, then shadow map, then compute bindings, then the engine call-site migration to the path API.

- [x] **Step 2: Check and commit**

Run `git diff --check`, stage only source, tests, docs and the plan, then commit and push.
