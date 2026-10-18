# D3D12 shadow map — design and implementation plan

Status: approved for execution
Baseline: `192d632d` (master)
Backends affected: D3D12 only. GL/Vulkan are the reference and must not change
behaviour.

## Goal

Implement the four shadow-map entry points that are currently no-ops in
`engine/src/rhi/rhi_d3d12.c`, plus the two helpers they depend on, so the
cascaded-shadow pass can render and sample on D3D12:

| Entry point | Current D3D12 state | Line |
| --- | --- | --- |
| `rhi_shadow_map_create` | returns a zeroed handle | `rhi_d3d12.c:3783` |
| `rhi_shadow_map_destroy` | no-op | `rhi_d3d12.c:3789` |
| `rhi_cmd_bind_shadow_map` | no-op | `rhi_d3d12.c:3792` |
| `rhi_cmd_unbind_shadow_map` | no-op | `rhi_d3d12.c:3795` |
| `rhi_cmd_bind_shadow_texture` | no-op | `rhi_d3d12.c:3615` |
| `rhi_cmd_transition_depth_to_read` | no-op | `rhi_d3d12.c:4628` |

## Correcting a claim recorded in the previous round

`docs/Implementation_Status.md` and the long comment at `rhi_d3d12.c:3548-3577`
both state that shadow binding is blocked because D3D12 has no comparison
sampling. **That is wrong for this path, and the docs must be corrected as part
of this work.**

The engine never declares `sampler2DShadow` or `samplerCubeShadow`. The
production clustered forward shaders sample shadows with a *manual* compare on
the raw `.r` channel:

- `engine/shaders/blinn_phong_clustered.frag:70-71`
  `float depth = texture(u_point_shadow_cubes[shadow_idx], frag_to_light).r;`
  followed by `compare <= depth + u_shadow_bias ? 1.0 : 0.15`
- `engine/shaders/blinn_phong_clustered_vk.frag:76-77` — same, identical
- `engine/shaders/pbr_clustered.frag`, `engine/shaders/deferred_light.frag` —
  same shape

And GL explicitly turns hardware comparison *off* for that reason:

- `engine/src/rhi/rhi_gl.c:3809-3811`
  `/* R215-A: Shaders use samplerCube + .r manual compare (not
  samplerCubeShadow). COMPARE_REF_TO_TEXTURE makes non-shadow sampler reads
  undefined. */` then `glTexParameteri(GL_TEXTURE_CUBE_MAP,
  GL_TEXTURE_COMPARE_MODE, GL_NONE)`

The D3D12 test suite confirms the type is rejected outright if declared:
`engine/tests/test_shader_io.c:497` asserts `sampler2DShadow` is rejected by the
reflection parser.

A grep for `sampler2DShadow|samplerCubeShadow` across the tree returns only
that test and the GL comment — there is no production declaration anywhere.

So the D3D12 static LINEAR sampler plus a plain `SRV` is sufficient, and the
manual compare in the shader works unchanged. **The comparison-sampler limit
stays documented as a real limitation of the root-signature design, but it is
not what blocks the shadow pass, and saying otherwise in the status doc is a
factual error that must be fixed.**

## The real D3D12 constraint: `DXGI_FORMAT_D32_FLOAT` is not sampleable

A depth-stencil view can be created from `DXGI_FORMAT_D32_FLOAT`, but that
format cannot back a shader resource view. A shadow map has to be *both*:

- the DSV the depth pass renders into, and
- the SRV the lighting pass samples.

D3D12 solves this with a typeless alias pair. Allocate the resource as
`DXGI_FORMAT_R32_TYPELESS` with
`D3D12_RESOURCE_FLAG_ALLOW_DEPTH_STENCIL`, then create two views over it:

- DSV with `Format = DXGI_FORMAT_D32_FLOAT` (depth-stencil aspect)
- SRV with `Format = DXGI_FORMAT_R32_FLOAT` (shader-resource aspect)

Both views address the same 4-byte-per-pixel depth data, and
`glTexParameterfv(GL_TEXTURE_BORDER_COLOR, {1,1,1,1})`-equivalent behaviour
falls out of the shader's manual compare against a depth value of `1.0`, so no
border mode is needed on D3D12.

`rhi_texture_create` today maps `RHI_FORMAT_D32_FLOAT` straight to
`DXGI_FORMAT_D32_FLOAT` (`rhi_d3d12.c:2903`, table at `:55`) and sets
`td->dxgi_format` to it, so the SRV that `rhi_cmd_bind_texture` builds at
`:3595` (`srv.Format = td->dxgi_format`) would be rejected. This is the same
latent defect that `rhi_cmd_transition_depth_to_read` being a no-op hides.

## Design

### 1. `RHI_D3D12Texture` gains one field

```c
typedef struct RHI_D3D12Texture {
    ID3D12Resource *resource;
    DXGI_FORMAT dxgi_format;
    DXGI_FORMAT srv_format;       /* DXGI_FORMAT_UNKNOWN = same as dxgi_format */
    ...
} RHI_D3D12Texture;
```

`srv_format` is the format to put in a shader resource view. It equals
`dxgi_format` for every ordinary texture, so existing behaviour is unchanged by
construction. It is only set for depth textures that need to be sampled.

### 2. `rhi_texture_create` gains an internal depth-aliasing flag

The public entry point becomes a one-line wrapper over a new static worker:

```c
static RHITexture rhi_d3d12_texture_create_ex(RHIDevice *dev,
                                              const RHITextureDesc *desc,
                                              int depth_samplable);
RHITexture rhi_texture_create(RHIDevice *dev, const RHITextureDesc *desc) {
    return rhi_d3d12_texture_create_ex(dev, desc, 0);
}
```

Inside the worker, when `desc->format == RHI_FORMAT_D32_FLOAT && depth_samplable`:

- `description.Format = DXGI_FORMAT_R32_TYPELESS` (the allocation)
- `clear_value.Format = DXGI_FORMAT_D32_FLOAT` (the depth-stencil aspect)
- `td->dxgi_format = DXGI_FORMAT_R32_TYPELESS`
- `td->srv_format = DXGI_FORMAT_R32_FLOAT`
- `td->rhi_format = RHI_FORMAT_D32_FLOAT` — unchanged, so every existing
  depth-side behaviour keyed on `rhi_format` keeps working unchanged:
  `rhi_d3d12_texture_final_state` still returns `DEPTH_WRITE` (`:2882`),
  `rhi_texture_read_pixels` still reports the RHI-level depth format, and
  `pso.DSVFormat = DXGI_FORMAT_D32_FLOAT` (`:2723`) still matches.

Everything else (upload path, mip counts, validation, slot registration) is
shared with the existing function. Initial data is rejected for a depth
texture by the existing `rhi_texture_desc_validate` path, so the upload branch
needs no depth-specific handling.

`rhi_cmd_bind_texture` then picks the SRV format through one helper:

```c
static DXGI_FORMAT rhi_d3d12_srv_format(const RHI_D3D12Texture *td) {
    return td->srv_format != DXGI_FORMAT_UNKNOWN ? td->srv_format
                                                 : td->dxgi_format;
}
```

used at `:3595`. A plain depth texture (offscreen FBO depth, MRT depth) still
gets `DXGI_FORMAT_D32_FLOAT` and is still unsamplable, exactly as today.

### 3. `rhi_shadow_map_create`

Mirrors `rhi_gl.c:2639-2704` step for step:

1. `rhi_drawable_dimensions_valid(width, height)` gate, returning
   `(RHIShadowMap){0}` — the same invalid-atlas gate GL has, so
   `rhi_cmd_bind_shadow_map` can never clear someone else's depth.
2. `rhi_d3d12_texture_create_ex(dev, &desc, /*depth_samplable=*/1)` with
   `desc.format = RHI_FORMAT_D32_FLOAT`, `mip_levels = 1`, `data = NULL`.
3. Take a descriptor slot from `ctx->dsv_alloc` (same allocator the offscreen
   FBO uses at `:4206`) and
   `ID3D12Device_CreateDepthStencilView(ctx->device, depth->resource, &dsv_desc
   /* Format = DXGI_FORMAT_D32_FLOAT */, cpu_handle)`.
4. Register an `RHI_RES_FRAMEBUFFER` slot wrapping the DSV slot, so
   `rhi_cmd_bind_shadow_map` resolves it through the same typed lookup the
   offscreen bind uses at `:4287`.

Every failure path destroys what it built and returns a zeroed handle, so a
partially-built atlas is never published — the D3D12 counterpart of GL's
R358 `glCheckFramebufferStatus` gate. D3D12 has no equivalent completeness
check because `CreateDepthStencilView` either succeeds or returns a failed
HRESULT; the corresponding hazard on D3D12 is publishing a handle whose DSV
slot is `UINT_MAX`, which the descriptor-take step already prevents.

`sm.width` / `sm.height` are set so the shadow viewport can be derived without
re-querying the texture.

### 4. `rhi_shadow_map_destroy`

Mirrors `rhi_gl.c:2706-2721`: destroy the depth texture, return the DSV slot
to `ctx->dsv_alloc`, free the `RHI_RES_FRAMEBUFFER` slot, and null both handles
so a double destroy is a no-op. The slot return goes through
`rhi_d3d12_retire_fence` + `rhi_d3d12_descriptor_give_back`, the deferred
pattern the FBO teardown at `:4208-4212` uses, because a command list may
still hold the descriptor.

### 5. `rhi_cmd_bind_shadow_map`

Mirrors `rhi_gl.c:2723-2745`:

1. Fail closed if `sm == NULL` or `sm->fbo` is not a live `RHI_RES_FRAMEBUFFER`
   — never fall through to the currently-bound DSV.
2. Resolve the DSV descriptor, transition the depth texture
   `DEPTH_WRITE -> DEPTH_WRITE` (no-op if already there) and call
   `OMSetRenderTargets(0, NULL, NULL, 1, &dsv)` — a depth-only pass. The
   shadow-depth PSO already sets `NumRenderTargets = 0` for
   `is_shadow_depth` (`rhi_d3d12.c:2698`), so this is consistent.
3. Set `ctx->bound_dsv` / `bound_dsv_valid = 1` so `rhi_cmd_clear_depth`
   (`:3798`) works against the atlas too.
4. Full-atlas viewport and scissor `(0, 0, sm->width, sm->height)` with depth
   range 0..1. D3D12's viewport depth range is already 0..1, so this matches
   GL's `gl_set_depth_range_cached(0.0f, 1.0f)` without a state variable.
5. Clear depth to 1.0 over the whole atlas with the scissor wide open —
   the R618 "bind == fresh" contract from `rhi.h:668-673`, and the GL
   R259 correction about the depth write mask has no D3D12 analogue because
   `ClearDepthStencilView` honours the PSO's `DepthWriteMask`, and the
   shadow-depth PSO always sets `D3D12_DEPTH_WRITE_MASK_ALL`
   (`:2695-2696` — `depth_write_disable` is false for a shadow pass).

Per-cascade quadrants are applied afterwards by the existing
`rhi_cmd_set_shadow_viewport` (`rhi_d3d12.c:3395`), which already exists and is
already correct.

### 6. `rhi_cmd_unbind_shadow_map`

Mirrors `rhi_gl.c:2747-2753` (bind target 0 + full-screen viewport). On D3D12
"target 0" is the swapchain, so the body is the same as
`rhi_offscreen_fbo_unbind` (`:4321-4344`): bind the current swapchain RTV,
`bound_dsv_valid = 0`, viewport and scissor to `(0, 0, screen_w, screen_h)`,
`MinDepth = 0, MaxDepth = 1`.

### 7. `rhi_cmd_bind_shadow_texture`

Mirrors `rhi_gl.c:2490-2494`, which is `gl_bind_tex_unit(1, shadow_tex,
sampler)` — material unit 1. On D3D12 this is the existing
`rhi_cmd_bind_texture(cmd, shadow_tex, sampler, 1u)`, which now works because
`srv_format` gives the SRV `DXGI_FORMAT_R32_FLOAT` instead of the unsamplable
`DXGI_FORMAT_D32_FLOAT`. The sampler argument stays discarded, which is
correct for this path (manual compare, LINEAR filter per GL's NEAREST/NEAREST
setup being an approximation the shaders already tolerate — noted, not changed).

### 8. `rhi_cmd_transition_depth_to_read`

Mirrors the intent used by `rhi_cmd_bind_texture`'s inline transition: move a
depth texture from `DEPTH_WRITE` to
`PIXEL_SHADER_RESOURCE | NON_PIXEL_SHADER_RESOURCE` and update `td->state`.
This is the function the Vulkan path relies on after its render pass; on
D3D12 the equivalent transition already happens inside `rhi_cmd_bind_texture`,
but the entry point must not stay a silent no-op for callers that use it
explicitly. It must also handle the "already in a read state" case as a no-op.

## Tests

All additions go in `engine/tests/test_d3d12_warp_runtime.c`, which already
provides a WARP device, an offscreen FBO harness and per-pixel assertions
(`ASSERT_EQ` on raw RGBA bytes). Nine cases currently pass there; these are
added on top.

New sidecars under `engine/shaders/`:

- `shadow_depth_hlsl.vert` — POSITION-only vertex input, transforms a quad by a
  root constant, writes `SV_Position` only. No colour output.
- `shadow_sample_hlsl.frag` — samples the shadow depth SRV at `t1` with a
  static sampler `s1`, does the manual compare `coord.z - bias <= depth ? 1 : 0`
  and emits that as greyscale.

`shadow_sample_hlsl.frag` must use the manual compare rather than a
`SamplerComparisonState` — this is the test that pins the corrected claim
above. A reviewer changing it to a hardware comparison sampler should find the
test failing, not passing.

Cases:

1. `shadow_map_create_publishes_a_depth_target` — a created atlas has a valid
   `depth_tex` and `fbo`; `rhi_get_resource_typed(sm.fbo, RHI_RES_FRAMEBUFFER)`
   resolves; destroy nulls both handles and survives a second destroy.
2. `shadow_bind_clears_the_atlas_to_one` — bind, then sample the atlas through
   a depth-read SRV and assert every texel reads `1.0`. Pinned by
   `docs/receipts` render? No — asserted in-test by reading back through the
   R32_FLOAT SRV via a blit into an RGBA8 FBO (D3D12 cannot `CopyTextureRegion`
   out of a depth-stencil resource without a compatible copy region, so the
   readback goes through the same sampling path the lighting pass uses, which
   is the thing actually under test).
3. `shadow_depth_pass_writes_and_the_lighting_pass_sees_it` — full round trip:
   depth-only pipeline into the atlas at z = 0.25, then the sampling shader
   reads it and must return 1.0 (lit) in the region the quad covered and 0.0
   outside it. This is the pixel-level proof that DSV and SRV alias the same
   bytes; if the typeless pair were wrong, the values would not match.
4. `shadow_unbind_restores_the_screen_target` — after bind + unbind, a
   subsequent offscreen draw still lands in its own FBO (mirrors the R230
   parity note already in `rhi_offscreen_fbo_unbind`).
5. `shadow_sampled_depth_matches_the_depth_pass_writes` — a second quadrant at
   z = 0.75 through `rhi_cmd_set_shadow_viewport`, confirming the CSM quadrant
   path and the clear-then-draw ordering.

### Reverse verification (mandatory)

Observed results on WARP, each break applied, observed, reverted, and the
suite returned to green:

| # | Deliberate break | Result |
| --- | --- | --- |
| A1 | allocate plain `DXGI_FORMAT_D32_FLOAT` instead of the typeless alias | **stayed GREEN — not observable on WARP.** Both formats are 4 bytes/texel and WARP tolerates the SRV reinterpretation. The typeless allocation stays because the spec requires it for hardware drivers, but no pixel proves it. |
| A2 | leave `srv_format` unknown so the SRV names `DXGI_FORMAT_D32_FLOAT` | RED (the invalid SRV takes the device down; the readback one-shot fails) |
| B | bind the shadow SRV at unit 0 instead of 1 | RED at the pixel assertion |
| C | drop the `OMSetRenderTargets` depth-only bind | RED at the pixel assertion |
| D | clear to `0.0` instead of `1.0` | RED at the pixel assertion |
| E | drop the barrier into the read state in `rhi_cmd_bind_texture` | RED at the pixel assertion |

A1 is recorded rather than hidden: it is a real limitation of what a WARP
receipt can establish about this feature, and the test's header comment says
so explicitly.

### Gates

- `build-d3d12-debug`: `ctest -R "d3d12|warp|swapchain"` → 12/12 plus the new
  cases.
- `build-d3d12-debug`: `ctest -LE graphics` → 176 total, only
  `test_platform_win32_runtime` (clipboard unavailable in this session) and
  the five `EXCLUDE_FROM_ALL` fuzz smoke tests failing.
- `build-gl` and `build-vk`: `ctest -LE graphics` → 175/175 and 176/176, same
  single clipboard failure. These must not move at all; the change is D3D12-only.
- `test_no_hidden_gl_fallback` scans raw file text for backend tokens. Any
  comment written in the D3D12 file that names the GL *file* will trip it —
  refer to GL by function name, or state the rule without naming a file. Do not
  add a whitelist entry; that would permanently exempt the whole D3D12 backend.

## Documentation

- `docs/Implementation_Status.md:27` — the "静态采样器限制" bullet. Its
  closing claim, that shadow map and point-shadow cubes "在 GL 上是经比较采样器
  采样的，在 D3D12 上今天根本做不了深度比较" and therefore block the forward
  pass, is false and must be replaced with the manual-compare finding and the
  typeless-alias constraint that actually applied. Keep the sampler limitation
  itself, relabelled as affecting only future hardware-compare shaders.
- `docs/Implementation_Status.md:39` — the step-② paragraph that orders
  "shadow map 卡在采样器，不是卡在渲染" and forbids drawing the shadow pass
  first. That ordering constraint exists precisely to avoid shipping a
  silently-wrong frame, and it was derived from the false claim above. It must
  be rewritten: the real prerequisite is the typeless DSV/SRV alias, which
  lands in this round, and the ordering rule dissolves with it.
- `docs/Implementation_Status.md` — this file is also where the D3D12
  per-entrypoint state is recorded (the round-3 section starting at `:5`).
  Add the six entry points moving out of the stub column there.
- `engine/src/rhi/rhi_d3d12.c`: rewrite the KNOWN LIMIT comment at `:3548-3577`
  to state the real limitation (no per-unit sampler, no comparison sampling for
  *future* hardware-compare shaders) without claiming it blocks the shadow
  pass.

## Work breakdown

1. `RHI_D3D12Texture.srv_format` + `rhi_d3d12_texture_create_ex` +
   `rhi_d3d12_srv_format` + the one-line change in `rhi_cmd_bind_texture`.
   **Gate: full D3D12 + GL + VK suites green before continuing.** This step
   alone must be behaviour-neutral for every existing texture.
2. `rhi_shadow_map_create` / `rhi_shadow_map_destroy`.
3. `rhi_cmd_bind_shadow_map` / `rhi_cmd_unbind_shadow_map`.
4. `rhi_cmd_bind_shadow_texture` / `rhi_cmd_transition_depth_to_read`.
5. Sidecars + the five test cases.
6. Reverse verification A–E.
7. Documentation.

Steps 1–4 are one commit if each of 2/3/4 is independently compile-clean, or
three commits split at the natural seams above; the test and documentation work
is a separate commit either way, because the reverse-verification record belongs
with the tests, not with the implementation.
