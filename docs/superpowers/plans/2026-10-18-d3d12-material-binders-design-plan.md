# D3D12 Material Texture Binders Implementation Plan

> **For agentic workers:** REQUIRED SUB-SKILL: Use superpowers:subagent-driven-development (recommended) or superpowers:executing-plans to implement this plan task-by-task. Steps use checkbox (`- [ ]`) syntax for tracking.

**Goal:** Implement the D3D12 material texture binders so a forward draw samples its albedo through the real binder path, verified with WARP pixels.

**Architecture:** The binders mirror the GL unit map exactly, so a D3D12 sidecar that declares `Texture2D g_albedo : register(t0)` lines up with GL texture unit 0. Each bind goes through the existing `rhi_cmd_bind_texture`, which already resolves the root descriptor table for a register and writes an SRV. Because D3D12 descriptors are not "unset" the way GL texture units are, an invalid texture handle must resolve to a 1x1 white fallback so the shader never samples garbage.

**Tech Stack:** C11, D3D12 Agility SDK, WARP runtime tests, CMake/Ninja.

## Global Constraints

- Mirror the GL unit map exactly: unit 0 = albedo, 1 = shadow, 2 = mr, 3 = normal, 4 = emissive, 5 = ssao. Do not renumber.
- A D3D12 sidecar's `register(tN)` must correspond to GL texture unit N. The blinn_phong sidecar already declares `register(t0)` for albedo, so unit 0 binds albedo.
- Invalid texture handles must bind a 1x1 white fallback texture, never leave a descriptor unwritten.
- Do not change GL, Vulkan, the engine's forward path, or the blinn_phong sidecar.
- Verify with WARP pixels, not handle existence alone.
- Do not commit generated DXIL, build outputs, or scratch files.

---

### Task 1: Implement the D3D12 Material Binders and the White Fallback

**Files:**
- Modify: `engine/src/rhi/rhi_d3d12.c`
- Modify: `engine/src/rhi/rhi_d3d12.h`

**Interfaces:**
- Consumes: the existing `rhi_cmd_bind_texture` (SRV creation plus root descriptor table), `RHI_D3D12Context`, the GL reference at `engine/src/rhi/rhi_gl.c:2400`.
- Produces: `rhi_cmd_bind_material_textures` and `rhi_cmd_bind_material_textures_ibl` with GL-equivalent behavior on D3D12.

- [ ] **Step 1: Add a lazily created 1x1 white fallback texture**

Give the D3D12 context one small helper that returns a shared 1x1 RGBA8 white texture, created on first use and released with the context. Use it whenever a material texture handle is invalid, so a bound descriptor is always well defined.

- [ ] **Step 2: Implement `rhi_cmd_bind_material_textures`**

For each of the six GL units (0 albedo, 1 shadow, 2 mr, 3 normal, 4 emissive, 5 ssao) call `rhi_cmd_bind_texture(cmd, texture, sampler, unit)`, substituting the white fallback for an invalid handle. Skip a unit whose register the bound pipeline does not declare: `rhi_cmd_bind_texture` already returns without touching a table when the pipeline has no such register, so a sidecar that declares only `t0` still works.

- [ ] **Step 3: Implement `rhi_cmd_bind_material_textures_ibl`**

Mirror the GL version's unit map exactly, including occlusion at unit 15, ssao at unit 14, the point-shadow cubes at units 10-13, and the IBL cubemap units. The cubemap arguments are `RHICubemap` handles; on D3D12 cubemaps are not implemented yet, so those units must be left unbound and that limitation stated in a comment, exactly as the GL version's cubemap branch would behave with an invalid handle.

- [ ] **Step 4: Build the D3D12 backend**

Run:
```bash
cd E:/work/break/build-d3d12-debug
ninja
```

Expected: zero compiler errors and warnings.

---

### Task 2: Prove the Binder Path Renders on D3D12

**Files:**
- Modify: `engine/tests/test_d3d12_warp_runtime.c`

**Interfaces:**
- Consumes: `rhi_cmd_bind_material_textures`, the blinn_phong sidecar pipeline, the existing offscreen FBO and readback helpers.
- Produces: a WARP test proving the real binder path reaches the shader.

- [ ] **Step 1: Write the test**

Extend the existing blinn_phong sidecar test, or add a sibling test that:
1. Builds the blinn_phong pipeline from the sidecar as the existing test does.
2. Creates a 2x2 red texture and an invalid handle to stand in for a missing material map.
3. Calls `rhi_cmd_bind_material_textures(cmd, red, invalid, invalid, invalid, invalid, invalid, sampler)` so albedo lands on unit 0 and the invalid handles take the fallback path.
4. Draws into an 8x8 offscreen FBO and asserts every pixel is red.

The invalid handles matter: they prove the fallback path produces a valid descriptor instead of leaving garbage.

- [ ] **Step 2: Run it and confirm it fails before the implementation is complete**

Run:
```bash
cd E:/work/break/build-d3d12-debug
ninja test_d3d12_warp_runtime
ctest -R test_d3d12_warp_runtime -V
```

Expected before the binder exists: the draw samples an unwritten descriptor and the assertion fails, or the binder is a no-op and the pixel is wrong.

- [ ] **Step 3: Make it pass**

Implement only what the test needs on top of Task 1.

- [ ] **Step 4: Reverse validation**

Break one thing at a time and confirm each turns the test red: swap the albedo unit to 1, and remove the fallback substitution. Restore both and confirm green.

- [ ] **Step 5: Run the specialist suites**

Run:
```bash
cd E:/work/break/build-d3d12-debug
ctest -R "d3d12|warp|swapchain" --output-on-failure
cd ../build-gl && ctest -LE graphics --output-on-failure
cd ../build-vk && ctest -LE graphics --output-on-failure
```

Expected: D3D12 specialist tests pass; GL and Vulkan unchanged apart from the known `test_platform_win32_runtime` clipboard environment failure.

---

### Task 3: Document and Commit

**Files:**
- Modify: `docs/Implementation_Status.md`

**Interfaces:**
- Consumes: the verified binders and their pixel evidence.
- Produces: documented binder behavior, the fallback rule, and the remaining ordered work.

- [ ] **Step 1: Document**

Record the mirrored GL unit map, the white fallback rule and why D3D12 needs it, the WARP pixel proof with reverse validation, the cubemap limitation, and the remaining order: shadow map, compute bindings, then the FORWARD_MRT velocity output and the engine call-site migration to the path API.

- [ ] **Step 2: Check and commit**

Run `git diff --check`, stage only source, tests, and docs, then commit and push.
