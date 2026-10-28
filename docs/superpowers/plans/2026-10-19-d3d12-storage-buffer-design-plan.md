# D3D12 storage-buffer binding — design and implementation plan

Status: approved for execution
Baseline: `19489e77` (master)
Backends affected: D3D12 only.

## Goal

`rhi_cmd_bind_storage_buffer` (`rhi_d3d12.c:4786`) is an empty stub, so no
compute shader on D3D12 has ever received an SSBO. This round lands the UAV
path: the pipeline-side register→root-parameter map the binder needs, the
binder itself, a compute sidecar, and a WARP test that reads the result back
as pixels.

## Correcting a prediction recorded earlier

An earlier note said this step "must first solve a register-space collision:
the reflector collapses the HLSL register class into `kind`, so
`RWStructuredBuffer<u0>` and `Texture2D<t0>` both land at `binding=0`, and
keying on register alone collides with `image_root_params`."

**That is not a real problem, and no redesign is needed.** The root-signature
builder (`rhi_d3d12_root_sig_add_bindings`, `rhi_d3d12.c:2467`) already keys by
**two independent arrays per kind** — `image_root_params[tN]` and
`uniform_root_params[bN]` — each indexed by its own register number, and only
the matching kind writes its own array:

```c
if (bind->kind == SHADER_IO_RESOURCE_IMAGE && bind->binding < 16u)
    b->image_root_params[bind->binding] = b->param_count - 1u;
if (bind->kind == SHADER_IO_RESOURCE_UNIFORM && bind->binding < 16u)
    b->uniform_root_params[bind->binding] = b->param_count - 1u;
```

A compute shader declaring `Texture2D t0` **and** `RWStructuredBuffer u0`
therefore gets two independent root parameters — an SRV range at register 0 and
a UAV range at register 0 — which is legal D3D12, because a UAV and an SRV at
the same register number are different descriptor types in different tables.
Adding `storage_root_params[uN]` follows the existing pattern exactly. The
`kind`-vs-register-class question does not need to be resolved in the
reflector, and `ShaderIOBinding` gains no new field.

## STATUS: NOT LANDED — this plan was executed and reverted

Implementation was written and bisected on WARP; the device is removed by
something in the bind and the cause was not isolated. The whole code change was
reverted rather than shipped unproven. Read
`docs/Implementation_Status.md` (the "compute binding" round entry) for the
bisect table and the next experiments.

Two predictions in this plan are wrong and are corrected here so the next
attempt does not repeat them:

1. **There is no register-space collision to solve.** The root-signature
   builder already keys `image_root_params[tN]` and `uniform_root_params[bN]` as
   independent per-kind arrays, each written only by its own kind. A compute
   shader declaring `Texture2D t0` and `RWStructuredBuffer u0` gets two
   separate root parameters — an SRV range at register 0 and a UAV range at
   register 0 — which is legal, since they are different descriptor types in
   different tables. Adding `storage_root_params[uN]` follows the pattern; the
   reflector needs no change and `ShaderIOBinding` gains no field.

2. **`rhi_cmd_memory_barrier` is not a stub.** It already records a global
   `D3D12_RESOURCE_BARRIER_TYPE_UAV` (NULL resource = every UAV on the list).
   The section below claiming it was left a stub and a silent-correctness gap
   does not hold.

## The real constraint: resource state

`RHI_D3D12Buffer` tracks a `state`, and a storage buffer does **not** arrive in
a UAV-compatible state in general. `rhi_d3d12_buffer_wants_device_local`
(`:1864`) returns false for a storage buffer with no `initial_data`, so it
lands on the UPLOAD heap in `D3D12_RESOURCE_STATE_GENERIC_READ`
(`:1946-1948`). `GENERIC_READ` does not permit `UNORDERED_ACCESS` writes — a
UAV descriptor over it is a validation error.

The binder therefore transitions to `D3D12_RESOURCE_STATE_UNORDERED_ACCESS`
before writing the descriptor, tracking `bd->state` the same way
`rhi_cmd_bind_texture` does for textures and `rhi_offscreen_fbo_bind` does for
its depth attachment. A buffer already in that state costs no barrier.

## Design

### 1. `RHI_D3D12Pipeline` gains `storage_root_params[16]`

Keyed by the **u-register number**, mirroring `image_root_params`. Written by
the builder at the same point the other two maps are written:

```c
if (bind->kind == SHADER_IO_RESOURCE_STORAGE && bind->binding < 16u)
    b->storage_root_params[bind->binding] = b->param_count - 1u;
```

and copied into the pipeline in the same loop that fixes up the other two maps
for the push-constant param shift (`:2847`). A register of 16 or more leaves
the entry at its `UINT_MAX` initialiser, which is the same "not declared" the
other two maps express.

The builder struct (`RHI_D3D12RootSigBuilder`) grows the array alongside, so
it is zero-initialised the same way. `calloc` must be confirmed to cover it —
the existing arrays rely on that too.

### 2. `rhi_cmd_bind_storage_buffer`

Mirrors `rhi_cmd_bind_uniform_buffer` (`:3670`), which is the closest
analogue: take a descriptor slot, write the view, set the root table, return
the slot.

```c
param = pd->storage_root_params[binding];  /* UINT_MAX = not declared */
```

Steps:

1. Gate on `ctx`, `g_current_device`, `binding < 16u`, a bound pipeline and a
   live command list — the same gates `bind_uniform_buffer` uses.
2. `param == UINT_MAX` → return. A register the pipeline never declared is a
   silent no-op, matching the SRV and CBV binders.
3. Resolve the buffer through `rhi_get_resource_typed(..., RHI_RES_BUFFER)`.
   Unlike the material slots there is **no white-fallback analogue**: a
   descriptor table entry pointing at nothing is exactly the failure the
   fallback rule exists to prevent, so an unresolvable buffer returns without
   writing. That is a "the draw will sample the previous contents" failure
   rather than a crash, and it matches what the uniform-buffer binder already
   does.
4. Transition `bd->state` → `UNORDERED_ACCESS` if it differs.
5. Take a slot from `ctx->cbv_srv_uav_alloc`. The CBV/SRV/UAV heap is a single
   mixed heap and UAV descriptors are legal in it; a UAV descriptor in the
   non-shader-visible CBV/SRV/UAV heap is equally legal, and this is the heap
   that is already bound for every pipeline.
6. `ID3D12Device_CreateUnorderedAccessView` with
   `Format = DXGI_FORMAT_UNKNOWN` (typed-as-unknown is required for a
   structured buffer) and `StructureByteStride` left zero unless the buffer
   declares a stride. The engine has no stride on `RHIBufferDesc`, and GL's
   `glBindBufferBase(GL_SHADER_STORAGE_BUFFER, ...)` carries none either — the
   HLSL side must declare `StructuredBuffer<T>` and index it in elements.
7. `SetGraphics/ComputeRootDescriptorTable`, chosen by `pd->is_compute`, exactly
   as `bind_uniform_buffer` does. Storage buffers appear in graphics pipelines
   too on the clustered paths, so both branches are needed.
8. Give the slot back with `ctx->next_fence`, the same deferred pattern
   `bind_uniform_buffer` uses — the descriptor is not reusable until that fence
   completes.

### 3. What this round deliberately does not touch

- **`rhi_cmd_bind_texel_buffers`** (`:4045`). A texel buffer is an SRV over a
  buffer, bound at fixed units 5/6 as a `TEXTURE_BUFFER` on GL. It needs a
  `D3D12_SRV_DIMENSION_BUFFER` view with a `StructuredByteStride`, which the
  RHI has nowhere to express (`RHIBufferDesc` has no stride field). Doing it
  properly is a vertex-fetch change, not a compute-binding one, and no D3D12
  sidecar declares a texel buffer yet.
- **`rhi_cmd_bind_image_texture`** (`:4807`). The storage-image surface: a UAV
  over an `RWTexture2D`, which is a separate descriptor shape with its own
  format/array/mip questions.
- **`rhi_cmd_memory_barrier`** (`:4795`). Already a stub on D3D12. Compute
  writers do need a UAV barrier between dispatches that share a buffer, but the
  shader-visible ordering this needs is not automatic on D3D12; leaving it a
  stub while the first compute shader lands would be shipping a silent
  correctness gap. **This is flagged as the next item rather than hidden** —
  the test below uses one dispatch followed by a CPU readback, which the
  existing fence wait already orders, so it does not depend on a barrier.

### 4. Test sidecar

`storage_rw_hlsl.comp` — a compute shader that writes a known pattern into a
`RWStructuredBuffer<float4>` at `u0`:

```hlsl
RWStructuredBuffer<float4> g_out : register(u0, space0);
[numthreads(1, 1, 1)]
void main(uint3 tid : SV_DispatchThreadID) { g_out[tid.x] = ...; }
```

Values are chosen so that a dropped descriptor, a wrong register and a stale
descriptor are all distinguishable in the resulting pixels.

### 5. Test case

`storage_buffer_binder_reaches_the_shader` in `test_d3d12_warp_runtime.c`:

1. Create a compute pipeline from the sidecar; assert the handle is valid
   (which also proves the compute path can build a root signature with a UAV
   range at all).
2. Create a `RHI_BUFFER_USAGE_STORAGE` buffer big enough for 64 `float4`s.
3. Dispatch once with `numthreads(1,1,1)` and the shader writing a known
   pattern.
4. Read the buffer back with `rhi_buffer_map` (or the existing readback helper)
   and assert the exact bytes.

The pixel stage of the proof is the follow-on draw: a graphics pipeline samples
the storage buffer through a `StructuredBuffer` SRV and blits the value into an
8x8 FBO, so the result is asserted as **pixels** rather than as bytes. That
also proves the UAV state transition left the buffer readable as an SRV, which
a pure CPU readback would not.

### 6. Reverse verification

| # | Deliberate break | Expected |
| --- | --- | --- |
| A | bind at `storage_root_params[0]` unconditionally instead of indexing by `binding` | red if the shader declares a register other than 0 |
| B | skip the `UNORDERED_ACCESS` transition | red — the buffer is in `GENERIC_READ` |
| C | build the descriptor with the buffer's byte length zeroed | red |
| D | drop the `pd->is_compute` branch (always graphics) | red |
| E | revert `rhi_cmd_bind_storage_buffer` to the empty stub | red |

### 7. Gates

- `build-d3d12-debug`: `ctest -R "d3d12|warp|swapchain"` → 12/12 plus the new
  case.
- `build-d3d12-debug`: `ctest -LE graphics` → 170/176, failures unchanged
  (`test_platform_win32_runtime` clipboard + five `EXCLUDE_FROM_ALL` fuzz
  smokes).
- `build-gl`, `build-vk`: `ctest -LE graphics` → 174/175, 175/176, clipboard
  only. These must not move; the change is D3D12-only.
- `test_no_hidden_gl_fallback` scans raw file text for backend tokens. Refer
  to the GL backend by function name, not by file name, and do not add a
  whitelist entry.

## Documentation

- `docs/Implementation_Status.md`: move `rhi_cmd_bind_storage_buffer` out of
  the stub column in the round entry, record the register-class finding as a
  non-issue (the earlier note predicted a collision that the per-kind arrays
  already prevent), and record `rhi_cmd_memory_barrier` as the named next
  item with its silent-correctness-gap reason.

## Work breakdown

1. `storage_root_params` on the pipeline and the builder, plus the copy loop.
   **Gate: all three backends green before continuing** — this step must be
   behaviour-neutral for every existing pipeline, since it only adds a map that
   nothing reads until step 2.
2. `rhi_cmd_bind_storage_buffer`.
3. `storage_rw_hlsl.comp` sidecar.
4. The test case.
5. Reverse verification A–E.
6. Documentation.
