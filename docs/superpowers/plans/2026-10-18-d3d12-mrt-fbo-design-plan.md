# D3D12 MRT FBO Implementation Plan

> **For agentic workers:** REQUIRED SUB-SKILL: Use superpowers:subagent-driven-development (recommended) or superpowers:executing-plans to implement this plan task-by-task. Steps use checkbox (`- [ ]`) syntax for tracking.

**Goal:** Implement D3D12 multiple-render-target framebuffer creation, binding, loading, unbinding, destruction, and pixel-level WARP verification without changing GL/Vulkan behavior.

**Architecture:** Reuse the existing D3D12 texture/resource and descriptor allocator paths. An MRT FBO owns one RHI color texture plus RTV descriptor per attachment and one D32 depth texture/DSV; bind records resource-state transitions, binds all RTVs/DSV, clears according to the existing RHI contract, and unbind restores the swapchain target. MSAA and cubemap MRT variants remain fail-closed until resolve/cubemap support is explicitly implemented.

**Tech Stack:** C11, D3D12 Agility SDK, CMake/Ninja, Clang on Windows, WARP runtime tests, existing `rhi_texture_read_pixels` readback.

## Global Constraints

- Preserve GL/Vulkan behavior; all new runtime behavior is gated inside `engine/src/rhi/rhi_d3d12.c` and `.h`.
- Keep D3D12 state transitions based on `RHI_D3D12Texture.state`; never assume an ambient resource state.
- Return an invalid/zero FBO for unsupported MSAA instead of silently downgrading it.
- Use fence-retired RTV/DSV descriptor slots; never return an in-flight descriptor immediately.
- Test with WARP pixels, not handle existence alone.
- Do not commit generated build outputs, screenshots, `.tmp`, or other untracked scratch files.

---

### Task 1: Map the Existing MRT Contract

**Files:**
- Read: `engine/src/rhi/rhi.h:730-825`
- Read: `engine/src/rhi/rhi_gl.c` and `engine/src/rhi/rhi_vk.c` MRT FBO implementations
- Read: `engine/src/rhi/rhi_d3d12.c:3600-4120`
- Read: `engine/src/rhi/rhi_d3d12.h:90-180`

**Interfaces:**
- Consumes: `RHIMRTFBO`, `RHIMRTFBODesc`, `rhi_mrt_fbo_*` declarations, `rhi_texture_create`, descriptor allocator, `rhi_d3d12_transition`.
- Produces: A written implementation checklist in the task notes: attachment count limits, color/depth ownership, clear/load semantics, unbind target restoration, and unsupported MSAA behavior.

- [ ] **Step 1: Record the exact public MRT fields and limits**

Run:
```bash
cd E:/work/break
grep -n "typedef struct.*RHIMRTFBO\|RHIMRTFBODesc\|rhi_mrt_fbo_" engine/src/rhi/rhi.h
```

Expected: capture `color_tex[]`, `depth_tex`, `attachment_count`, dimensions, sample count, and all public bind/unbind functions before editing.

- [ ] **Step 2: Compare GL/VK clear/load behavior**

Run:
```bash
cd E:/work/break
grep -n "rhi_mrt_fbo_bind\|rhi_mrt_fbo_bind_load\|rhi_mrt_fbo_unbind" engine/src/rhi/rhi_gl.c engine/src/rhi/rhi_vk.c
```

Expected: document that `bind` is fresh/clearing, `bind_load` preserves, and `unbind` restores the screen target and viewport/scissor.

- [ ] **Step 3: Confirm the D3D12 descriptor and resource helpers**

Run:
```bash
cd E:/work/break
grep -n "rhi_d3d12_descriptor_take\|rhi_d3d12_descriptor_give_back\|rhi_texture_create\|rhi_d3d12_transition" engine/src/rhi/rhi_d3d12.c
```

Expected: identify exact helper signatures before implementation; do not introduce a second allocator or barrier helper.

---

### Task 2: Add D3D12 MRT Ownership Data

**Files:**
- Modify: `engine/src/rhi/rhi_d3d12.h` near `RHI_D3D12FBO`
- Modify: `engine/src/rhi/rhi_d3d12.c` near D3D12 FBO/resource definitions

**Interfaces:**
- Consumes: `RHI_D3D12Context.rtv_alloc`, `RHI_D3D12Context.dsv_alloc`, `RHIMRTFBO` public shape.
- Produces: Internal `RHI_D3D12MRTFBO` with `rtv_slots[RHI_MRT_MAX_ATTACHMENTS]`, `dsv_slot`, `width`, `height`, `attachment_count`, `sample_count`, and a clear-color array initialized to the RHI default.

- [ ] **Step 1: Add internal MRT state fields**

Add an internal structure with these exact fields:
```c
UINT rtv_slots[RHI_MRT_MAX_ATTACHMENTS];
UINT dsv_slot;
UINT width, height, attachment_count, sample_count;
float clear_color[RHI_MRT_MAX_ATTACHMENTS][4];
```
Initialize all descriptor slots to `UINT_MAX` so partial allocation cleanup is unambiguous.

- [ ] **Step 2: Add the resource lifetime helpers**

Implement internal cleanup that:
1. Gives each non-`UINT_MAX` RTV/DSV slot back with `rhi_d3d12_descriptor_give_back(ctx_allocator, slot, rhi_d3d12_retire_fence(ctx))`.
2. Frees the framebuffer slot with `rhi_free_slot`.
3. Destroys each color/depth RHI texture after descriptor release.
4. Zeroes the public `RHIMRTFBO`.

- [ ] **Step 3: Build and run the existing D3D12 specialist suite**

Run:
```bash
cd E:/work/break/build-d3d12-debug
ninja
ctest -R "d3d12|warp|swapchain" --output-on-failure
```

Expected: existing 12 specialist tests remain green; no MRT behavior is exposed yet.

---

### Task 3: Implement MRT Create/Destroy

**Files:**
- Modify: `engine/src/rhi/rhi_d3d12.c` D3D12 MRT FBO stubs around `rhi_mrt_fbo_create`

**Interfaces:**
- Consumes: `RHIMRTFBODesc`, `rhi_offscreen_fbo_desc_validate`-style validation, `rhi_texture_create`, descriptor allocator.
- Produces: `rhi_mrt_fbo_create`, `rhi_mrt_fbo_create_desc` if declared, and `rhi_mrt_fbo_destroy` that return valid public handles only after all resources/descriptors succeed.

- [ ] **Step 1: Validate dimensions, formats, attachment count, and sample count**

Reject:
- zero dimensions;
- attachment count `0` or greater than `RHI_MRT_MAX_ATTACHMENTS`;
- unsupported color formats;
- `sample_count > 1`.

For `sample_count > 1`, return a zeroed `RHIMRTFBO`; do not create single-sample resources as a silent fallback.

- [ ] **Step 2: Create color and depth textures**

For each color format, call `rhi_texture_create` with width/height/mip level 1. Create one D32 depth texture. On any failure, destroy every already-created texture and return a zeroed FBO.

- [ ] **Step 3: Allocate RTV/DSV descriptors and create views**

Take one RTV slot per color attachment and one DSV slot. Call `ID3D12Device_CreateRenderTargetView` for each color texture and `ID3D12Device_CreateDepthStencilView` for depth. On partial allocation failure, return all taken slots through the fence-retired cleanup path.

- [ ] **Step 4: Register the MRT resource and initialize clear colors**

Store the internal `RHI_D3D12MRTFBO` in `dev->slots[]` with `RHI_RES_MRT_FBO`, set the public attachment handles/dimensions/sample count, and initialize every attachment clear color to `{0.05f, 0.05f, 0.1f, 1.0f}`.

- [ ] **Step 5: Build and run specialist tests**

Run:
```bash
cd E:/work/break/build-d3d12-debug
ninja
ctest -R "d3d12|warp|swapchain" --output-on-failure
```

Expected: 12/12 before adding the new pixel test.

---

### Task 4: Implement MRT Bind, Bind-Load, and Unbind

**Files:**
- Modify: `engine/src/rhi/rhi_d3d12.c` D3D12 MRT bind/unbind stubs

**Interfaces:**
- Consumes: public `RHIMRTFBO`, internal `RHI_D3D12MRTFBO`, `RHI_D3D12Texture.state`, `rhi_d3d12_set_full_target_viewport`.
- Produces: Native D3D12 RTV/DSV binding and correct target restoration.

- [ ] **Step 1: Implement shared bind helper**

For `bind` and `bind_load`, perform:
1. Validate command list, public FBO handle, and internal resource.
2. Transition every color texture from its tracked state to `D3D12_RESOURCE_STATE_RENDER_TARGET`; update each `state`.
3. Transition depth to `D3D12_RESOURCE_STATE_DEPTH_WRITE`; update `state`.
4. Build an array of RTV CPU handles and call `OMSetRenderTargets(count, rtvs, FALSE, &dsv)`.
5. Update `ctx->bound_rtvs`, `bound_rtv_count`, `bound_dsv`, and `bound_dsv_valid`.
6. Call `rhi_d3d12_set_full_target_viewport(list, width, height)`.

- [ ] **Step 2: Apply fresh-bind clears only**

For `bind`, call `ClearRenderTargetView` for every RTV with its stored clear color and `ClearDepthStencilView` with depth 1.0. For `bind_load`, skip both clears.

- [ ] **Step 3: Implement unbind target restoration**

Transition every color texture to the tracked shader-readable state and depth to its tracked read state when the existing RHI contract requires it. Bind the current swapchain RTV, clear DSV validity, and call `rhi_d3d12_set_full_target_viewport(list, screen_w, screen_h)`.

- [ ] **Step 4: Build and run specialist tests**

Run:
```bash
cd E:/work/break/build-d3d12-debug
ninja
ctest -R "d3d12|warp|swapchain" --output-on-failure
```

Expected: existing tests remain green.

---

### Task 5: Add WARP Pixel-Level MRT Verification

**Files:**
- Modify: `engine/tests/test_d3d12_warp_runtime.c`
- Test: `build-d3d12-debug/test_d3d12_warp_runtime.exe`

**Interfaces:**
- Consumes: new D3D12 MRT APIs, existing `rhi_texture_read_pixels`, WARP device setup.
- Produces: deterministic proof that two color attachments are independently bound, cleared, and readable.

- [ ] **Step 1: Write the failing pixel test**

Add a test with:
```c
RHIFormat formats[2] = {
    RHI_FORMAT_R8G8B8A8_UNORM,
    RHI_FORMAT_R8G8B8A8_UNORM
};
```
Create an 8x8 two-attachment MRT, set clear colors to red and blue, acquire a frame, call `rhi_mrt_fbo_bind`, then `rhi_mrt_fbo_unbind`, submit/present, and read both `color_tex[0]` and `color_tex[1]`. Assert every pixel in attachment 0 is red and every pixel in attachment 1 is blue.

- [ ] **Step 2: Run the test before implementation completion**

Run:
```bash
cd E:/work/break/build-d3d12-debug
ninja test_d3d12_warp_runtime
ctest -R test_d3d12_warp_runtime -V
```

Expected before the implementation is complete: FAIL because the D3D12 MRT create stub returns an invalid FBO.

- [ ] **Step 3: Implement the minimal test-enabling path**

Use only the public MRT bind/clear/unbind APIs; do not call internal D3D12 objects from the test.

- [ ] **Step 4: Run the passing test**

Run the same commands. Expected: PASS with all pixels in both attachments matching their independent colors.

- [ ] **Step 5: Perform reverse validation**

Temporarily change the expected blue channel for attachment 1 to a red-only expectation, run the test, and confirm it fails. Restore the correct expectation and rerun to PASS before committing.

---

### Task 6: Full Regression and Documentation

**Files:**
- Modify: `docs/Implementation_Status.md`
- Modify: `docs/Realtime_Raytracing_Progress.md` only if its D3D12 status needs a matching entry

**Interfaces:**
- Consumes: completed MRT implementation and test evidence.
- Produces: documented D3D12 MRT support and clean remote commit.

- [ ] **Step 1: Run full D3D12 verification**

Run:
```bash
cd E:/work/break/build-d3d12-debug
ninja
ctest -R "d3d12|warp|swapchain" --output-on-failure
```

Expected: all D3D12 specialist tests pass.

- [ ] **Step 2: Run GL and Vulkan non-graphics regression**

Run:
```bash
cd E:/work/break/build-gl && ninja && ctest -LE graphics --output-on-failure
cd ../build-vk && ninja && ctest -LE graphics --output-on-failure
```

Expected: GL 175/175 and VK 176/176, with any known Windows platform environment failure recorded separately.

- [ ] **Step 3: Document exact behavior and boundaries**

Record:
- MRT create/bind/bind_load/unbind/destroy now work on D3D12;
- fresh bind clears every attachment and depth, bind_load preserves;
- MSAA remains fail-closed;
- WARP two-attachment pixel test and reverse validation passed;
- remaining cubemap/MRT-MSAA limitations.

- [ ] **Step 4: Check diff and commit**

Run:
```bash
cd E:/work/break
git diff --check
git status --short
```

Commit only source, tests, and docs. Do not add `.tmp`, build outputs, DXIL scratch files, screenshots, or existing untracked artifacts.

- [ ] **Step 5: Push and verify**

Run:
```bash
git push origin master
git status -sb
```

Expected: branch is synchronized with `origin/master`.
