# D3D12 Shader Path API Implementation Plan

> **For agentic workers:** REQUIRED SUB-SKILL: Use superpowers:subagent-driven-development (recommended) or superpowers:executing-plans to implement this plan task-by-task. Steps use checkbox (`- [ ]`) syntax for tracking.

**Goal:** Give the D3D12 backend access to the engine's shader file path so it can resolve hand-authored HLSL sidecars, verified end to end with a WARP pixel test.

**Architecture:** Add a path-based shader creation entry point to the RHI. GL and Vulkan read the file and compile it exactly as they do today. D3D12 maps the GLSL path to its `*_hlsl.<stage>` sidecar and loads the precompiled DXIL, reusing the existing filename-mode loader. The public shader struct and pipeline creation are unchanged.

**Tech Stack:** C11, D3D12 Agility SDK, CMake/Ninja, Clang on Windows, WARP runtime tests.

## Global Constraints

- Do not change GL/Vulkan rendering behavior; their path-based path must compile the same GLSL text the engine passes today.
- Do not change the public `RHIShader` shape or `rhi_pipeline_create` semantics.
- The D3D12 sidecar naming convention is `<base>_hlsl.<stage>` next to the GLSL source in `engine/shaders`.
- Use the existing D3D12 filename-mode loader; do not add a second DXIL loading path.
- Verify with WARP pixels, not handle existence alone.
- Do not commit generated build outputs, DXIL artifacts, screenshots, or scratch directories.

---

### Task 1: Add the Path-Based Shader Entry Point

**Files:**
- Modify: `engine/src/rhi/rhi.h` (declaration next to `rhi_shader_create`)
- Modify: `engine/src/rhi/rhi_gl.c`
- Modify: `engine/src/rhi/rhi_vk.c`
- Modify: `engine/src/rhi/rhi_d3d12.c`

**Interfaces:**
- Produces: `RHIShader rhi_shader_create_path(RHIDevice *dev, const char *path, bool is_fragment);` and `RHIShader rhi_shader_create_compute_path(RHIDevice *dev, const char *path);`
- GL/Vulkan: read the file at `path`, then delegate to the existing text-based `rhi_shader_create` with the read length, preserving today's compile behavior exactly.
- D3D12: derive the sidecar base name from `path` (strip directory and extension, append `_hlsl`), then use the existing filename-mode loader.

- [ ] **Step 1: Declare the new entry points in `rhi.h`**

Add next to the existing declarations, with a comment stating the D3D12 sidecar convention and that other backends compile the file's GLSL.

- [ ] **Step 2: Implement the GL and Vulkan variants**

Read the file with the existing `shader_read_file` helper, then call the existing `rhi_shader_create` / `rhi_shader_create_compute` with the read buffer and length. Free the buffer after creation, and return `RHI_HANDLE_NULL` if the file cannot be read.

- [ ] **Step 3: Implement the D3D12 variant**

Derive the sidecar name: take the path's final component, strip the extension, and append `_hlsl.vert` or `_hlsl.frag` (or `.comp` for the compute variant). Pass that bare file name to the existing filename-mode loader so the HLSL source and precompiled DXIL are loaded exactly as the current contract tests do.

- [ ] **Step 4: Build all three backends**

Run:
```bash
cd E:/work/break/build-gl && ninja
cd ../build-vk && ninja
cd ../build-d3d12-debug && ninja
```

Expected: zero compiler errors and warnings in each tree.

---

### Task 2: Prove Path Resolution with a WARP Pixel Test

**Files:**
- Modify: `engine/tests/test_d3d12_warp_runtime.c`

**Interfaces:**
- Consumes: `rhi_shader_create_path`, the existing `blit_hlsl` sidecar pair, existing MRT/offscreen FBO and texture readback helpers.
- Produces: a WARP test proving a GLSL-style path resolves to its sidecar and that the resulting pipeline renders.

- [ ] **Step 1: Write the failing test**

Create a test that:
1. Calls `rhi_shader_create_path(g_dev, "shaders/blit_hlsl.vert", false)` and the `.frag` counterpart.
2. Asserts both handles are valid.
3. Builds a pipeline with `no_vertex_input` and the blit color format.
4. Draws a fullscreen triangle into an 8x8 offscreen FBO while binding a known 2x2 red texture through `rhi_cmd_bind_texture`.
5. Reads the FBO color texture back and asserts every pixel is red.

- [ ] **Step 2: Run and confirm it fails before implementation is complete**

Run:
```bash
cd E:/work/break/build-d3d12-debug
ninja test_d3d12_warp_runtime
ctest -R test_d3d12_warp_runtime -V
```

Expected before the D3D12 path variant exists: the path entry point is undeclared or returns an invalid handle, and the test fails.

- [ ] **Step 3: Make it pass**

Implement only what the test needs on top of Task 1.

- [ ] **Step 4: Reverse validation**

Temporarily change one expected channel so the assertion must fail, confirm the test turns red, then restore and confirm green.

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
- Consumes: verified implementation and test evidence.
- Produces: documented path-resolution contract and the remaining D3D12 renderer-pipeline work.

- [ ] **Step 1: Document the finding and the change**

Record: the engine passes GLSL text and drops the path, so D3D12 could never resolve a sidecar; the new path entry point restores that; GL/Vulkan semantics unchanged; the WARP path-resolution pixel test and reverse validation results; and the remaining work (hand-authoring `*_hlsl.*` sidecars per renderer pipeline, then material binders, shadow map, and compute bindings, in that order).

- [ ] **Step 2: Check and commit**

Run `git diff --check`, stage only source, tests, and docs, then commit and push.
