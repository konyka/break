# D3D12 FORWARD_MRT velocity / RT1 output — design

Status: all five steps implemented and verified (R600/R605/R606), plus two
follow-on subsystems carried to D3D12 on hand-written sidecars (R607
`blinn_phong_arr`, R608 skybox / water / terrain).
Baseline: `d77882e7` (master)
Backends affected: D3D12 sidecar design; one option changes the cross-backend
uniform contract.

## Why this blocks step ⑤

`engine/src/main.c:382-405` builds the production blinn_phong forward pipeline
with `FORWARD_MRT` unconditionally injected and
`mrt_attachment_count = 2u, mrt_formats = {R16G16B16A16_SFLOAT, R16G16_SFLOAT}`.
The path API (`rhi_shader_create_path`) maps only to the non-MRT sidecar pair
`blinn_phong_hlsl.{vert,frag}`, which declares `SV_Target` only. Migrating that
call site to the path API without RT1 would hand the engine a pipeline that
silently produces no velocity — a TAA frame with no motion information, which
looks like it runs and is wrong. So velocity/RT1 must land first.

## The shader contract (from the GLSL twin)

`engine/shaders/blinn_phong.vert`:
- extra `layout(std140, binding = 0) uniform ForwardTemporal { mat4 u_prev_vp; mat4 u_prev_model; }`
- `out vec2 v_velocity` = `curr_clip.xy/curr_clip.w - prev_clip.xy/prev_clip.w`

`engine/shaders/blinn_phong.frag`:
- `in vec2 v_velocity`, `layout(location = 1) out vec2 out_velocity`
- `out_velocity = v_velocity` alongside the existing `FragColor`

## The data already exists

`main.c:598-609` — `rs->clustered_proj_ubo` is
`{ prev_vp, prev_model, proj }` at offsets 0/64/128, with the temporal pair
deliberately leading (R589: "so an accidental rebind into a
ForwardTemporal-expecting blinn pipeline still reads correct values"). So the
CBV's contents are produced per frame already; the D3D12 sidecar only has to
declare and bind it. **No new per-frame CPU work is required.**

## The hard constraint, verified against the code

`rhi_d3d12_root_signature_create` (`rhi_d3d12.c:2605`):

```c
max_dwords = table_params >= 64u ? 0u : 64u - table_params;
```

D3D12 root signatures are capped at 64 DWORDs total; every descriptor table
costs one. The base push block is 256B = 64 DWORDs, declared at
`push_constant_size = is_compute ? 128 : 256`.

The base block's tail is three `float3` light uniforms followed by
`u_camera_pos`:

| offset | member | bytes |
| --- | --- | --- |
| 0 | u_model | 64 |
| 64 | u_view | 64 |
| 128 | u_proj | 64 |
| 192 | u_light_dir | 16 (12 + pad) |
| 208 | u_light_color | 16 |
| 224 | u_ambient | 16 |
| 240 | u_camera_pos | 12 -> ends at **252** |

- **1 table** (today: `t0` albedo SRV) -> 63 DWORD = **252 B**.
  `rhi_push_range_fits(240, 12, 252)` -> `12 <= 252-240 = 12` -> **fits exactly.**
- **2 tables** (add `b1` temporal CBV) -> 62 DWORD = **248 B**.
  `rhi_push_range_fits(240, 12, 248)` -> `12 <= 248-240 = 8` -> **FALSE.**

`rhi_cmd_push_constants` (`rhi_d3d12.c:3797`) drops the write with a warning in
that case. So adding the temporal CBV **silently loses `u_camera_pos`**, which
the blinn_phong fragment shader uses for the view vector — the frame would
render with a wrong (zeroed) camera position and no visible error beyond a log
line. This is precisely the "dropped write is invisible to tests" trap, so it
must be designed around rather than discovered later.

The block cannot simply be reshuffled: three `float3`s after three `mat4`s are
always 4 x 16-byte slots, and HLSL cbuffer rules force the 4-byte hole that
makes the total 252 rather than 248. And the temporal data (128 B) cannot move
into root constants either — 248 B minus the 192 B of model/view/proj leaves
56 B, far short of two `mat4`s.

## Options

### Option B — move `u_camera_pos` into the temporal CBV (recommended)

Declare the sidecar's CBV as `{ float3 u_camera_pos; mat4 u_prev_vp; mat4
u_prev_model; }` (offsets 0 / 16 / 80). The push block then ends at 240 and
fits in 248 with room to spare. `u_camera_pos` is written through the CBV, which
the engine already binds per frame.

- One pipeline, one draw, no per-object cost.
- Matches what GL/VK already do structurally: the temporal data already rides a
  UBO there, so this removes a split rather than adding one.
- **Cost: it is a cross-backend contract change.** `u_camera_pos` moves out of
  the push block on D3D12 only unless the same move is made in the GLSL shaders
  and the GL/VK layout tables, in which case the change is uniform across
  backends. Leaving it D3D12-only would break the property this project keeps
  earning — that the D3D12 sidecar mirrors the GLSL twin field for field.

### Option D — split the MRT into two pipelines (D3D12-local)

A colour pipeline (t0 only, 1 table, 252 B, unchanged) and a velocity-only
pipeline (b1 only, 1 table, no `u_camera_pos` in its block at all, so its tail
is 240 and it fits comfortably).

- No contract change anywhere; strictly additive on D3D12.
- **Cost: two draws per object instead of one** on the production forward path,
  and the engine's draw loop, MRT bind and pipeline bind all need a second
  pass. That is a real per-frame cost on the path the whole renderer runs, for
  a capability only the sidecar needs.
- Also needs the MRT FBO bind to be able to target RT1 alone, which
  `rhi_mrt_fbo_bind` does not currently offer.

### Rejected: drop the write and move on

Declaring 248 B and letting `u_camera_pos` be dropped would render a wrong frame
behind a log line. Rejected on the same grounds as the dropped-write bugs this
project has already catalogued.

## Correction: Option B is larger than first stated

Writing this up surfaced a hole in Option B as originally scoped, which changes
its cost estimate materially.

`u_camera_pos` is used **unconditionally**:

```glsl
vec3 V = normalize(u_camera_pos - vWorldPos);   // blinn_phong.frag:25
```

but `ForwardTemporal` is declared only under `#ifdef FORWARD_MRT`. So moving
`u_camera_pos` into the temporal block does not just move one uniform — it forces
that block to exist for the non-MRT pipeline too. Concretely:

- **27 shader files** declare `u_camera_pos`; the blinn_phong family alone is
  `blinn_phong`, `blinn_phong_vk`, `blinn_phong_arr{,_vk}`,
  `blinn_phong_clustered{,_vk}` plus their `.hlsl` twins.
- **17 write sites** resolve and set `loc_camera_pos` in `main.c`.
- Only the clustered path binds `clustered_proj_ubo` today (`main.c:1196`);
  every other variant would need it bound, which means a new bind in each of
  their paths.

Option B therefore stops being "shift one uniform" and becomes "make the
temporal UBO unconditional for the whole forward family and rebind it
everywhere". That is a real contract change with a wide surface, and it is
correct — but it is not a one-round job, and shipping it without the budget to
reverse-verify it would break the rule this session has held to.

### A second observation that may shrink the problem

`main.c:1192` shows the base forward path already writes
`ubo_data[1] = mat4_identity()` — `u_prev_model` is **identity** for the
world-space mega vertices. Only the instanced variant reads a real per-instance
`prev_model` (from its SSBO). So for the base pipeline the temporal block could
reduce to `{u_prev_vp}` plus a camera position, i.e. 64 + 16 bytes. That does
not change the table count — the push range is still clamped to 248 by having
two tables rather than one — but it does mean the CBV is small enough that the
whole block could later move into root constants if the base block were shrunk,
which is worth recording before committing to either option.

## Recommendation

**Option B, applied uniformly across all three backends** so the D3D12 sidecar
keeps mirroring its GLSL twin. The work is:

1. Move `u_camera_pos` out of the base block into the temporal UBO in
   `blinn_phong.vert`/`.frag` and the `_vk` twins.
2. Extend `clustered_proj_ubo` to carry it (leading, so a stale rebind cannot
   feed a zeroed camera position) and widen its size from `3 * sizeof(Mat4)`.
3. Author `blinn_phong_hlsl.{vert,frag}` MRT variants: the CBV at `b1`, and
   `SV_Target1` for velocity.
4. Give the sidecar a way to be selected — today the only discriminator is the
   `FORWARD_MRT` define injected at runtime, and the path API resolves to a bare
   name with no variant selection. This is the same gap already recorded for
   variant parsing ("stay at the call site until the path API needs it").
5. Pixel proof on WARP: an 8x8 MRT FBO, a known `prev_vp`/`prev_model`, and an
   exact readback of both attachments — RT0 as the shaded colour, RT1 as the
   velocity, compared against the value computed on the CPU.

Until step 1 lands, step ⑤ (migrating `main.c:382` to the path API) stays
blocked, exactly as recorded.

---

## R600 — what actually shipped, and where the design was corrected

Option B landed. Three things in the write-up above turned out to be wrong or
under-specified, and the corrections are the interesting part.

### The temporal UBO is its own buffer, not `clustered_proj_ubo`

Step 2 said to extend `clustered_proj_ubo` to carry the camera position,
leading. That was wrong. `clustered_proj_ubo` is read by a *different* family
at a *different* layout: `pbr_clustered.vert` declares
`ClusterVertTemporal { mat4 u_prev_vp; mat4 u_prev_model; }` (or
`ClusterVertProj { mat4 u_proj; }` when `FORWARD_MRT` is off) at offsets
0/64/128, and the `CLUSTERED_ARR` factor tables start at 192. Putting a
16-byte camera header at the front would have silently shifted every one of
those readers — including the non-MRT `u_proj@0` read, i.e. the projection
matrix, on the default clustered path.

So the camera leads a **new** buffer, `rs->forward_temporal_ubo`
(`ForwardTemporalUbo { f32 cam_pos[3]; f32 cam_pad; Mat4 prev_vp;
Mat4 prev_model; }`, 144 B). `clustered_proj_ubo` keeps its layout and its
factor offsets untouched. "The camera leads the temporal block" is preserved —
it just leads a block that only the blinn family binds, which is the same
rule R589 stated without the false sharing.

### Scope is the blinn_phong family, not all 27 files

Step 1's own text names `blinn_phong.{vert,frag}` and the `_vk` twins. An
earlier pass in this session widened that to every shader declaring
`u_camera_pos` (`blinn_phong_arr`, `instanced`, `skinned`, `terrain`,
`water`, `particle`) and half-applied it — vertices converted to the block,
fragments left on the loose uniform. That is a GLSL link error, not a
warning: `blinn_phong_arr.frag` declaring a loose `uniform vec3
u_camera_pos` against `blinn_phong_arr.vert`'s block member fails to link,
and OpenGL reports it as `INTERNAL ERROR: Invalid Uniform variable name`,
which reads like a driver bug rather than a contract mismatch.

The wide scope was also not achievable on its own terms. Those variants are
GL-only in practice: D3D12 resolves `<base>_hlsl.<stage>`, and
`terrain_hlsl`/`water_hlsl`/`particle_hlsl` do not exist. And their draw paths
(`terrain.c`, `water.c`) resolve and write `u_camera_pos` as a loose uniform
with **no** UBO bind — converting the fragments would have left them reading
a never-bound buffer. Those edits are reverted. The 27-file / 17-write-site
surface in "Option B is larger than first stated" is real work; it is
recorded there as *future* scope, not done.

### Making a block unconditional moves the failure mode, it doesn't remove it

`ForwardTemporal` becoming unconditional means the blinn pipeline *statically
uses* the UBO descriptor set on Vulkan, so **every** draw of it must bind
that set — not just the ones that used to set a camera. Misses show up as
`VUID-vkCmdDrawIndexed-None-08600` ("set 1 is out of bounds for the number of
sets bound") plus a silently zeroed camera, which is exactly the
invisible-failure shape this design exists to avoid. Nineteen draw sites in
`test_vulkan.c` were converted to a `tv_bind_forward_temporal` helper for
this; the production path binds `forward_temporal_ubo` right after
`rhi_cmd_bind_pipeline(cmd, active_pipeline)`.

### What shipped

| Step | State |
| --- | --- |
| 1. `u_camera_pos` out of the base block, into the temporal UBO | done — `blinn_phong.{vert,frag}`, `blinn_phong_vk.{vert,frag}` |
| 2. buffer carries it, leading | done — new `forward_temporal_ubo`, see correction above |
| 3. `blinn_phong_hlsl` MRT sidecar | done — `blinn_phong_mrt_hlsl.{vert,frag}` (b1 CBV + `SV_Target1`) |
| 4. sidecar selection | done — the path API's `_hlsl` derivation is idempotent, so `shaders/blinn_phong_mrt.vert` resolves to `blinn_phong_mrt_hlsl.vert` with no new mechanism |
| 5. WARP pixel proof of RT0+RT1 | **not done** — the D3D12 forward path still loads GLSL sources at `main.c:403`, so step ⑤ remains blocked |

`test_shader_io`'s new `hlsl_blinn_sidecars_mirror_glsl_twin_after_camera_moved_to_cbv`
pins the sidecar half: no `rhi:uniform u_camera_pos` marker survives on any
of the four files (the marker table is what `rhi_pipeline_bindings_resolve`
reads, so its absence is what makes a dropped write visible), the `b1` CBV
is declared in all four, and only the MRT pair emits `SV_Target1`.

### Coverage this change does NOT have — recorded so it is not assumed

- **The golden scenes do not see the camera position.** Zeroing
  `ForwardTemporalUbo.cam_pos[0]` leaves both Vulkan golden MAEs at exactly
  28.75 / 13.54. The view vector only reaches the specular term on scenes
  the goldens do not cover. A pixel proof of the camera has to come from a
  new scene, not from the existing ones.
- **`test_vulkan`'s `UNIFIED GPU CULL TEST` is flaky on this host** — measured
  2 failures / 1 pass in three runs on unmodified `HEAD` (`7799b575`). Its
  `Hi-Z vis flags {0,0}` assertion is not a reliable gate signal here; an
  earlier note in this file recording it as "fixed" was one lucky run.
- **Step 5 (WARP pixel proof) is the only thing that would prove the
  velocity actually reaches RT1.** Everything above is contract-level.

### Pre-existing on this host, not caused by R600

`test_platform_win32_runtime` fails with `FAIL: OpenClipboard failed` (no
clipboard in this session) on unmodified `HEAD`. The GL/Vulkan golden
DRIFTs (15.60/1.15 and 28.75/13.54 against a MAE<=8 tolerance) and the GL
`MATERIAL ARRAY` quadrant vertical flip are also baseline.

### The gate口径 hid the one place this could break

The standing gate for this repo is `ctest -LE "graphics|fuzz"`. That
excludes the `graphics` label — and `test_d3d12_warp_runtime` carries it,
along with the D3D12 swapchain/pipeline/shader/DXR contracts. The first
commit of R600 passed every tree's gate while breaking two tests inside
that lane:

- `blinn_phong_sidecar_resolves_offsets_and_shades_red` pinned
  `u_camera_pos -> 240` and got `-1`;
- `material_binder_puts_albedo_on_t0_and_falls_back_to_white` asserted
  `loc[i] >= 0` for the same seven names.

Both are now on the R600 contract: `u_camera_pos` must resolve **-1**, and
the camera reaches the shader through `warp_forward_temporal_create` +
`rhi_cmd_bind_uniform_buffer(cmd, ubo, 1)`. The D3D12 graphics lane is
**8/8**. Run it explicitly — `ctest -L graphics` — not only the default
gate.

### Step 5, attempted: the blocker is now isolated to the sidecar

A WARP pixel proof for `blinn_phong_mrt_hlsl` was written (8x8 MRT FBO,
`{R8G8B8A8_UNORM, R16G16_SFLOAT}`, three draws with `u_prev_vp` scaled by
(1,1), (2,1) and (2,2), RT1 decoded from binary16). The assertions were
deliberately orientation-free — identity `u_prev_vp` must give exactly
+0.0 in both channels *on the raw 16 bits*, sx=2/sy=1 must pin one channel
to a hard zero while the other is live, and sx=2/sy=2 must make the
absolute-value multisets of the two channels match.

**It does not pass, and the test was removed rather than shipped red.** What
the attempt established, by bisection:

| Change | Result |
| --- | --- |
| MRT sidecar, MRT pipeline, MRT FBO, draw | device lost — `rhi_texture_read_pixels` returns false and every later test gets invalid handles |
| **non-MRT** sidecar, same MRT pipeline + FBO, draw | fine — RT0 is exactly red, device healthy |
| MRT sidecar, same setup, **no draw** | fine — RT0 reads back the clear, device healthy |

So the MRT FBO and the 2-RTV pipeline are both fine, and the defect is
inside the new sidecar path, not in the MRT infrastructure. Two further
observations from the run, both worth carrying forward:

- The D3D12 debug layer and GPU-based validation were enabled throughout and
  emitted **nothing**. Whatever kills the device is not a rule violation the
  validation layer knows about, so a pixel test alone will not find it.
- With the non-MRT sidecar, RT1 came back **non-zero** even though
  `rhi_mrt_fbo_bind` clears both attachments to (0,0,0,0). Either the
  D3D12 clear skips attachment 1, or the unwritten attachment is not what
  the clear left. Unrelated to R600, but it means an MRT test cannot assume
  a cleared RT1.

### Step 5, bisected: it is the vertex stage reading the CBV

Continuing the bisection past the three obvious differences, each change
built and run on WARP with the debug layer on:

| Variant | Device |
| --- | --- |
| MRT sidecar, full velocity (varying + `w` divide + `SV_Target1`) | **lost** |
| `SV_Target1` dropped, varying and divide kept | **lost** |
| `TEXCOORD3` dropped, divide kept | **lost** |
| `TEXCOORD3` dropped and divide replaced by `rcp()` | **lost** |
| `TEXCOORD3` dropped, divide and `prev_clip` dropped — VS reads `g_temporal.u_camera_pos` only | **lost** |
| `TEXCOORD3` kept, **no CBV read in the VS at all** | fine |
| non-MRT sidecar pair, **vertex shader** given a CBV read | **lost** |

The last row is the whole result: the same `register(b1)` cbuffer, read by
the pixel stage, works in every configuration above; read by the **vertex**
stage it loses the device, on a single-target pipeline with no second
render target, no extra varying and no divide.

Ruled out by experiment, not by argument:

- **Heap.** A CBV must point at a DEFAULT-heap resource, and
  `rhi_d3d12_buffer_wants_device_local` sent `RHI_BUFFER_USAGE_UNIFORM`
  buffers to the UPLOAD heap. That looks like a real spec violation and
  probably is one, but forcing uniform buffers device-local changed
  nothing here, so the change was **not** shipped on an unproven theory.
- **CBV size.** `rhi_cmd_bind_uniform_buffer` rounds
  `SizeInBytes` up to 256 while the buffer is 144 B, so the view claims
  112 B past the resource. Backing the buffer to a full 256 B changed
  nothing.
- **The divide and `rcp()`**, **the `TEXCOORD3` varying**, **`SV_Target1`**,
  and **the second render target** — each removed in turn.

The D3D12 debug layer and GPU-based validation were enabled for every one
of these runs and emitted nothing, so the usual tool for this class of
fault does not see it either.

### The blocker is WARP, not the backend

The same edit, on the same machine, on the other adapter:

| Adapter | `register(b1)` read by the vertex shader |
| --- | --- |
| WARP (`ENGINE_D3D12_WARP` set) | device lost |
| RTX 4060 (that variable unset) | **fine** — every other assertion in the suite passes |

`rhi_d3d12_pick_adapter` selects WARP on the *presence* of
`ENGINE_D3D12_WARP`, not its value, so `ENGINE_D3D12_WARP=0` still gets WARP;
the hardware run needs the variable unset plus
`BREAK_D3D12_TEST_FALLBACK_HWND=1` (there is no real HWND in this session).

That reframes everything above. The root signature, the descriptor tables,
the CBV size, the heap and the shader are all **correct**; the D3D12 backend
is not broken here. WARP faults on a vertex-stage constant-buffer view, and
this project's own evidence rule already says WARP receipts "never upgrade
the evidence level past GPU-runtime" — WARP is a floor, not the authority.

Two consequences worth acting on:

- **The engine is not blocked.** A D3D12 forward path whose vertex shader
  reads `u_prev_vp` / `u_prev_model` from the b1 CBV works on hardware,
  which is what step 5 needs.
- **The WARP suite cannot carry this proof.** Any test that has the vertex
  stage read a descriptor-bound CBV has to be hardware-gated, or it will
  report a WARP limitation as an engine failure. That is a test-infrastructure
  decision, not a shader one, and it is the next thing to settle.

Running the RT1 proof on hardware gets past everything the WARP run could
not: the pipeline builds, RT0 is exactly red on every draw, and the readback
succeeds. It then stops at the RT1 content assertion — draw 0 expects both
velocity channels to be exactly `+0.0` with an identity `u_prev_vp` and
finds something else. That is a genuine open question and is NOT explained
by anything above; the obvious next check is whether RT1 is written at all
versus holding its post-clear contents, and that needs the pixel dump this
round did not manage to land cleanly.

### What the RT1 attachment actually does on hardware

Chasing the last open question — is RT1 written at all, or is it holding
post-clear contents? — by making the fragment shader write **known
constants** and reading the attachment back as raw binary16 on the RTX 4060:

| Fragment shader writes | RT1 reads back | verdict |
| --- | --- | --- |
| `float2(0.25, -0.5)` | `3400 b800` on every pixel | **RT1 is bound, written and read back exactly** |
| `velocity` from the varying, `u_prev_vp` = identity | `7fff 7fff` | NaN, not zero |
| VS emits a **constant** varying `(0.75, 0.5)` | `3a00 3800` exactly | VS->PS varying link is fine |
| VS emits `curr_clip.xy / curr_clip.w` | `baff baff`, `b8ff baff`, ... | garbage |
| VS emits `curr_clip.wx` | first channel `3c00` = **1.0**, second `-128`, `-255`, ... | **w is exactly right, x is garbage** |

That last row is the whole remaining problem, and it is a small one. The
push constants **do** reach the vertex stage — `curr_clip.w` reads back as
exactly `1.0`, which is only true if model, view and proj are the identity
matrices the test wrote. A *constant* varying survives the trip. A varying
carrying a computed `curr_clip.x` does not.

So the open item is no longer "does RT1 work" (it does) or "do the uniforms
reach the VS" (they do). It is: **a non-constant vertex output does not
survive to the pixel stage on this path**, while the same varying with a
constant value does. Candidates, in the order they are worth checking:

1. `float2` at TEXCOORD3 as the fifth PS input — the input-layout
   reflection only describes the VS *input*; nothing checks the VS *output*
   against the PS *input*, and the MRT PS has five inputs where its sibling
   has four. Worth testing `float4` or moving the varying.
2. Register pressure / interpolator count on SM 6.0 for this signature.
3. The oversized test triangle: `curr_clip.x` spans -1..3 at the vertices,
   so the interpolant genuinely leaves [-1,1] before the divide. That would
   explain large magnitudes, but **not** why `curr_clip.wx` shows w exactly
   right in the same interpolant.

Nothing here is shipped. The test stays out until the varying is explained,
because a pixel proof that passes for the wrong reason is worse than none.

### The defect, stated as narrowly as the evidence allows

Five hypotheses tested, all dead. The last round closed the loop by
running each one on **hardware** as well as WARP, which is what turned
"invisible garbage" into "reproducible garbage":

| Change | WARP | RTX 4060 |
| --- | --- | --- |
| uniform buffers forced to the DEFAULT heap | no change | no change |
| CBV backed to its full 256 B | no change | no change |
| duplicate descriptor tables removed | no change (PSO then `E_INVALIDARG`) | **no change** — the non-MRT pipeline still renders the wrong colour once the VS reads the CBV |
| `float4` instead of `float2` for the varying | n/a | no change |
| my own fp16 decoder, which was wrong | n/a | **fixed** — see below |

The fp16 decoder in the proof was itself a bug worth recording: it used
`1u << (exp - 15)`, which is undefined for every value with magnitude below
1.0 — that is, most of a screen. It produced garbage that looked exactly
like a broken shader. `0xbaff` decodes to **-0.8745**, which is precisely the
NDC x of pixel 0 in an 8x8 target. So the varying is correct and always was.

Which leaves one fact, established from both sides:

> **The same `register(b1)` constant buffer, read by the pixel stage, arrives
> correct; read by the vertex stage, it arrives as garbage** — silently on
> hardware, and as device loss on WARP.

The proof that the pixel stage is correct is `RT0 is exactly red`: with the
camera read from that same CBV, a wrong or NaN camera would make `H` NaN and
carry NaN into the colour. It does not. The proof that the vertex stage is
not is `u_prev_vp` / `u_prev_model` coming back NaN and producing `7fff 7fff`
velocity.

Everything reachable from the buffer side is now exhausted: heap, view size,
table layout, descriptor lifetime, visibility, shader content, and adapter.
The remaining suspects are all inside `rhi_d3d12_root_signature_create` /
`SetGraphicsRootDescriptorTable` ordering and the per-stage reflection, and
finding them needs either the debug layer wired to a callback (its messages
go to OutputDebugString today, which is why it looked silent) or DRED output
on device loss. Neither is in place.

Nothing is shipped for any of this.

### The two observability gaps, and what is actually available

Step 5's diagnosis kept saying "the debug layer reported nothing", which
turned out to be two different problems:

**1. Messages were never routed anywhere readable.** Without a message
callback the layer writes to `OutputDebugString`, which a console test does
not see. That is the whole reason every earlier run looked silent.

**2. The callback cannot be installed with this SDK.** Writing it is a small
change, and it was written and then deleted: `ID3D12InfoQueue`,
`ID3D12Device_GetDebugInterface`, `D3D12_INFO_QUEUE_FILTER` and
`D3D12_MESSAGE_ID_CLEAR_*` are all **undeclared** by the D3D12 headers this
project compiles against. `D3D12GetDebugInterface` exists (DRED uses it) but
the info-queue API around it does not, so there is no supported way to turn
validation text into log lines here. Nothing shipped.

That leaves **DRED as the only machine-readable channel**, and it has a
precise limit worth stating: DRED reports a *page fault*, which requires the
device to be removed. WARP does remove the device, so DRED can say something
there. The hardware case never removes it — it silently returns wrong data —
so DRED is silent exactly where the interesting symptom lives. **No
validation channel can see the hardware failure**, which is why the
hardware symptom has to be attacked by reading the code and by targeted
instrumentation, not by waiting for a message.

Concretely, the next person should read, in this order:

1. `rhi_cmd_bind_uniform_buffer` — the descriptor is returned to the pool
   **in the same call** via `rhi_d3d12_descriptor_give_back(..., ctx->next_fence)`.
   If `rhi_cmd_bind_texture` takes a slot from the same allocator, it can
   overwrite the CBV descriptor before the GPU runs. Check the heaps: the
   bind path uses `cbv_srv_uav_alloc`, and it is worth confirming the texture
   path does not share it.
2. `rhi_d3d12_root_signature_create` — the 32BIT_CONSTANTS param is inserted
   by shifting `b->params`, and `uniform_root_params[i]++` compensates. With
   the duplicate tables still present, that shift interacts with which table
   index the vertex stage actually resolves.
3. The per-stage reflection merge itself — `rhi_d3d12_reflect_hlsl` is run
   once per stage over the same `bindings` array and both results are fed to
   the builder, so the array's contents and the `count` handling are worth
   re-reading closely.

Instrumentation that would answer it without any of the above: log
`pd->uniform_root_params[1]` and the descriptor handle actually bound, at
bind time, for the draw that misbehaves.

### The instrumentation run: a definite defect, provable from the code alone

`rhi_cmd_bind_uniform_buffer` now logs the slot, the root parameter and the descriptor handle. On the failing draw, on hardware:

    DIAG ubo bind: slot=4095 root_param=2 gpu=...12FFE0 buf=...17DCD000 size=256

`root_param=2` is the finding. The root signature is:

| index | contents | ever bound? |
| --- | --- | --- |
| 0 | 32BIT_CONSTANTS | yes, at flush |
| 1 | CBV `b1`, **VISIBILITY_VERTEX** (from the vertex pass) | **no** |
| 2 | CBV `b1`, **VISIBILITY_PIXEL** (from the pixel pass) | yes |
| 3 | SRV `t0`, **VISIBILITY_VERTEX** | **no** |
| 4 | SRV `t0`, **VISIBILITY_PIXEL** | yes |

Only two `SetGraphicsRootDescriptorTable` sites exist (`rhi_d3d12.c:3695` and `:3738`), and each binds exactly one table. So **root parameters 1 and 3 are never set, ever**, and D3D12 requires every descriptor-table parameter in the root signature to be set before a draw. A vertex shader reads `b1` through parameter 1; a pixel shader reads it through parameter 2, which is the one that was bound. That is the entire asymmetry, and it needs no driver bug to explain it.

**This part is settled and does not depend on the rest of the investigation.** The duplicate per-stage tables are a real defect, provable by reading the builder, not merely correlated with the symptom.

What is *not* yet explained is why deduplicating them did not make the vertex-stage read correct (it also introduced an `E_INVALIDARG` on the MRT PSO). Either the dedupe had a defect of its own, or something beyond the duplicate tables is also wrong. Those are now two separate questions, and the first one is small and well specified: collapse the two per-stage tables into one per (kind, register, space) with OR-ed visibility, and make sure every descriptor-table parameter the signature declares is actually bound before a draw — which is worth asserting in a test rather than assuming.

### The fix, implemented and audited -- and why it is not landed

The dedupe was written properly this time (reuse the matching range, OR the
visibility, keep the reused param index) and the resulting root signature was
dumped for every pipeline before it is serialised:

    param 0: non-table            <- 32BIT_CONSTANTS
    param 1: type=2 reg=1 vis=5   <- CBV b1, ALL stages
    param 1: type=0 reg=0 vis=5   <- SRV t0, ALL stages

No duplicate tables, one table per register, visibility correct, and both
bound. **The root signature the dedupe produces is provably right**, and that
part of the story is finished.

It is still not shipped, because with the corrected signature the blinn_phong
pipelines stop building: `rhi_pipeline_create` returns NULL for both
`blinn_phong_sidecar_resolves_offsets_and_shades_red` and
`material_binder_puts_albedo_on_t0_and_falls_back_to_white`, with no shader
compile warning and no error from `CreateRootSignature`. The other pipelines
(blit, probe, shadow) build fine, which is consistent with the earlier
`E_INVALIDARG` on the MRT PSO: whatever rejects a blinn or MRT pipeline is
specific to having a **CBV table alongside the texture table**, and it was
being masked before by the extra tables.

So the state is:

- **Settled**: the per-stage duplicate tables are a real defect; a correct
  root signature is achievable and audited; the vertex/pixel asymmetry is
  fully explained by unbound root parameters 1 and 3.
- **Not settled**: why a correct signature with a CBV plus an SRV table fails
  to produce a pipeline. That is a new, smaller, well-isolated question, and
  it is the right next thing -- it no longer has the duplicate-table confound
  in it.
- **Not landed**: nothing. The vertex-stage cbuffer read is still wrong, and
  shipping a half-fix that breaks pipeline creation would be worse than the
  current state, which at least builds.

The next step is therefore not "retry the dedupe" but "find out what
`CreateGraphicsPipelineState` dislikes about that signature" -- and now that
the signature is minimal and dumped, there is only one candidate left in it:
the CBV table and the SRV table coexisting in a **1.1 versioned** root
signature with a static sampler, which is exactly the configuration that was
never exercised before (the old signature duplicated the tables, which may
have been load-bearing in some way nobody has characterised).

### The PSO failure, located exactly

`CreateGraphicsPipelineState` was instrumented and run with the corrected
(deduped) root signature. Every pipeline in the suite:

    DIAG PSO hr=0x00000000 rtv=1 fmt0=28 fmt1=0    blit
    DIAG PSO hr=0x00000000 rtv=1 fmt0=28 fmt1=0    probe
    DIAG PSO hr=0x00000000 rtv=1 fmt0=28 fmt1=0    push-constants probe
    DIAG PSO hr=0x00000000 rtv=0 fmt0=0  fmt1=0    shadow (no colour target)
    DIAG PSO hr=0x80070057 rtv=1 fmt0=28 fmt1=0    blinn_phong   <- E_INVALIDARG

So it is **one pipeline**, it is **E_INVALIDARG**, and the difference between
it and `blit` -- which has the same push constants, the same single SRV table
and the same static sampler -- is exactly one thing: **the CBV table at
`b1`**. The MRT case is the same signature with two render targets and
behaves the same way.

That is a much sharper statement than "something about blinn". Concretely, the
open question is now:

> Why does `ID3D12Device_CreateGraphicsPipelineState` reject a 1.1-versioned
> root signature whose parameter list is `[0] 32BIT_CONSTANTS, [1] CBV b1,
> [2] SRV t0, static sampler s0` -- while accepting the same list with `[1]`
> absent?

Two things about this SDK make it worth writing down before anyone retries it:

- `D3D12_GRAPHICS_PIPELINE_STATE_DESC` here has **no `NumStaticSamplers`
  member**, so the PSO is created from the older struct while the root
  signature is serialised and created as **1.1**. That combination has never
  been exercised in this project, because the duplicated tables had been
  hiding it. Whether that struct/version pairing is the trigger is the first
  thing to check, and it is a one-line experiment: create the root signature
  as 1.0 and see whether the blinn PSO starts building.
- The duplicate tables may have been load-bearing for a reason nobody has
  characterised. They were wrong, but "wrong and load-bearing" is a
  combination that has to be resolved deliberately, not by deleting them and
  discovering the consequence.

Nothing shipped. The dedupe remains correct in principle and unlandable in
practice until this is answered.

### Narrowing the PSO failure further

Two single-variable runs against the deduped builder:

| blinn root signature | `CreateGraphicsPipelineState` |
| --- | --- |
| `[0]` constants, `[1]` CBV b1, `[2]` SRV t0, static sampler s0 | **E_INVALIDARG** |
| `[0]` constants, `[1]` SRV t0, static sampler s0 (CBV table suppressed entirely) | **E_INVALIDARG** |

The second row removes the CBV table, so "the CBV table is the trigger" is
**wrong**. It fails for a different and boring reason -- the blinn sidecars
still declare `ConstantBuffer<ForwardTemporal> g_temporal : register(b1)`,
so a signature without `b1` references a register the root signature does not
provide, which is itself invalid. Both directions fail.

What the two rows do establish is a much crisper statement than before:

> **blinn_phong builds with a five-parameter root signature and fails with a
> three-parameter one; blit builds with either.**

The only structural difference between those two blinn signatures and the
blit one is that the tables went from duplicated (two SRV + two CBV) to single
(one SRV + one CBV). Nothing else changed. So the trigger is a property of
the *reduced* parameter list, not of the CBV's presence, its register, or its
descriptor type.

The cheapest next experiment follows directly from that and needs no new
machinery: **add a dummy fourth descriptor-table parameter back** and see
whether blinn starts building. If it does, the count or the adjacency of the
parameters is what the driver rejects, and the fix is in how the builder lays
them out. If it does not, the problem is in the *content* of one of the three
parameters and each can be varied in turn.

Two caveats to carry forward:

- `D3D12_GRAPHICS_PIPELINE_STATE_DESC` in this SDK has no
  `NumStaticSamplers` member, so the PSO is built from the older struct while
  the root signature is serialised as **1.1**. That pairing has never been
  exercised here, because the duplicated tables hid it.
- The duplicate tables may be "wrong and load-bearing" -- an unidentified
  reason a five-parameter signature works where a three-parameter one does
  not. That is now the single most valuable thing left to find out, and it
  is answerable by bisection rather than by reasoning.

Nothing shipped.

### Step 4 closed: the production pipeline goes through the path API

`main.c` could not tell D3D12 from desktop GL: `shader_variant` is `GLSL` on
both, because D3D12 simply never assigns it. So the branch needed a new
capability rather than a reinterpretation of an existing one.

- `RHICapabilities.shader_sidecar_paths` — true only where
  `rhi_shader_create_path` resolves hand-authored sidecars. Set by all four
  backends that build a device (D3D12 true; GL, Vulkan, Metal false). It is
  deliberately not folded into `shader_variant`: that field reads back as
  `RHI_SHADER_VARIANT_GLSL` on D3D12, byte-identical to desktop GL, which is
  the whole reason the call site could not branch on what it had.
- `RHICapabilities.temporal_ubo_binding` — where the per-frame
  `ForwardTemporal` block has to be published: 0 in both GLSL twins
  (`binding = 0`), 1 in the D3D12 sidecars (`register(b1)`, because `b0` is
  the push block there). The register number is a fact only the backend
  knows, so the frame loop forwards it rather than recomputing it.

`render_init` now branches on `caps.shader_sidecar_paths`. The sidecar branch
asks for `shaders/blinn_phong_mrt.{vert,frag}`, which the idempotent `_hlsl`
derivation resolves to `blinn_phong_mrt_hlsl.{vert,frag}` -- the MRT pair,
because `pdesc` declares `mrt_attachment_count = 2`. The GLSL branch is the
previous read + `shader_inject_define` + create code, moved verbatim. Both
branches share the existing handle-validity cleanup.

**What this actually changed**: before it, `render_init` aborted on D3D12
with `Render init failed` -- a GLSL source has no DXIL blob, so
`rhi_pipeline_create` refused it, and the D3D12 forward path never
initialised at all. It now initialises:

    [INFO] main.c:429 blinn_phong: backend resolves shader sidecars; loading
           shaders/blinn_phong_mrt.{vert,frag} as blinn_phong_mrt_hlsl.{vert,frag}

The remaining `D3D12: pipeline needs compiled VS/PS blobs` warnings in the
demo come from the *other* subsystems -- terrain, clustered, deferred,
post-processing, skybox, water, IBL, particles, point-shadow -- which are
GLSL-only and still take the old path. They degrade with their existing
warnings; no gate covers them. `main.c`'s hot-reload pipeline is the next
call site in the same shape.

GL and Vulkan are untouched: both golden MAEs are byte-identical (15.60 /
1.15 and 28.75 / 13.54), and the emitted commands are unchanged because
`temporal_ubo_binding` evaluates to the same `0u` there.

### R607 -- the material-array variant follows, and D3D12 grows 2D arrays

`blinn_phong_arr` is the closest sibling of `blinn_phong`, so it got the same
five-part treatment: the R600 camera move in all four GLSL files (vert **and**
frag together, which is what the earlier reverted attempt got wrong), the
engine publishing through `forward_temporal_ubo`, new
`blinn_phong_arr_hlsl.{vert,frag}` sidecars, `render_init` branching on
`caps.shader_sidecar_paths`, and a WARP pixel proof.

**D3D12 had no 2D-array textures at all.** `rhi_texture_array_create`,
`rhi_texture_array_upload_layer` were stubs returning NULL and
`rhi_cmd_bind_texture` hard-coded `D3D12_SRV_DIMENSION_TEXTURE2D`, so the
proof was impossible until they were implemented: `array_size` plumbed into
`DepthOrArraySize`, a per-layer footprint + `CopyTextureRegion` upload with
the same host-OOB guard the GL backend uses, and an array-aware SRV emitting
`D3D12_SRV_DIMENSION_TEXTURE2DARRAY` with `ArraySize = layers`. Two naming
corrections worth keeping: `D3D12_TEX2D_ARRAY_SRV` uses `FirstArraySlice` /
`ArraySize`, and the enum is `D3D12_RESOURCE_STATE_INDIRECT_ARGUMENT`, not
`..._INDIRECT_COMMAND`.

That last one turned out to be a real latent bug: **nothing was putting the
indirect argument buffer into `INDIRECT_ARGUMENT` before `ExecuteIndirect`**,
which the API requires and which leaves the read undefined without it. Fixed
in the same pass.

The pixel proof makes the layer visible rather than asserting "not black": a
three-layer array (red / green / blue), two triangles tiled along a seam
chosen so no pixel centre lands on it, drawn with `InstanceCount` 2 and 3 so
the layer index decides the colour. All 64 pixels asserted exactly, exact
per-layer counts (0→64, 1→28, 2→36), RT1 asserted as raw binary16 zeros.
Negative-checked: replacing the layer with a literal `0.0f` in the frag turns
it red.

**⚠️ What this does NOT prove.** The production route is the layer arriving
via `first_instance` -- the indirect draw's `StartInstanceLocation`, which is
what `SV_InstanceID` reads. On WARP that is dropped: a record with
`StartInstanceLocation = 1 or 2` still yields `SV_InstanceID = 0` through this
very pipeline and shader, while `InstanceCount` works. So the test drives the
layer through the register it can observe and **the first-instance route is
unproven**. The DXIL disassembles to a single `dx.op.loadInput` on
`SV_InstanceID`, and real D3D12 hardware honours `StartInstanceLocation`,
so this reads as a WARP limitation rather than an engine defect -- but closing
it needs a real-GPU run of the same test through `rhi_cmd_draw_indirect`, and
until then the claim is one adapter short. The limitation and its evidence
are recorded in the test's header rather than left for the next reader to
rediscover.

### Step 5 closed: the RT1 velocity pixel proof passes

`blinn_phong_mrt_sidecar_writes_velocity_to_rt1` runs the blinn_phong MRT
sidecar into an 8x8 MRT FBO `{R8G8B8A8_UNORM, R16G16_SFLOAT}`, draws twice
and reads RT1 back as raw binary16. The assertions are deliberately
orientation-free, so a pass is about the velocity and not about the viewport
transform:

- **Draw A**, `u_prev_vp` identity: both velocity channels are exactly
  `+0.0`, asserted on the **raw 16-bit patterns**, so "approximately zero"
  cannot pass.
- **Draw B**, `u_prev_vp` scaled (2,1): velocity.y is exactly 0 on every
  pixel while velocity.x varies and takes both signs, and |velocity.x| stays
  inside [-1.01, 1.01] so a wrong divide-by-w shows up. One channel pinned
  to a hard zero while the other is live is what a correct per-channel read
  looks like; a missing or garbage attachment cannot produce it.
- **RT0 is exactly red on every draw** -- the regression guard on moving the
  camera onto the b1 cbuffer.

The arithmetic behind it: with identity model/view/proj the vertex stage
computes `curr = (x, y, 0, 1)` so `curr_ndc = (x, y)`, and for a diagonal
`u_prev_vp` of scale (sx, sy) with identity `u_prev_model`,
`velocity = ((1 - sx) * x, (1 - ty) * y)`.

**WARP 13/13.** Reverse-verified: with `rhi_d3d12.c` reverted to its
pre-R605 form the same test fails on readback and takes the rest of the suite
with it (9/13) -- so the proof is not passing for a reason unrelated to the
fix it exists to cover.

One thing this test also settles: the half-float decoder it needed. The first
version used `1u << (exp - 15)`, which is undefined for every value with
magnitude below 1.0 -- most of a screen -- and the garbage it produced read
exactly like a broken shader. `0xbaff` decodes to **-0.8745**, which is
precisely the NDC x of pixel 0 in an 8x8 target. Worth remembering as a class
of bug: a decoder bug in the oracle masquerades as a defect in the thing
under test.

**The plan is now complete.** See the next entry for step 4.

### R605 -- fixed, verified, landed

The premise of the last two entries was wrong and the fix is now in. Two
things had to be true at once, and the second one is the trap.

**1. The tables must be reused.** `rhi_d3d12_root_sig_add_bindings` now
scans the existing params for one whose single range matches
`(RangeType, BaseShaderRegister, RegisterSpace, NumDescriptors)`, records
the reused index in *both* `image_root_params` and `uniform_root_params`,
and skips creating a new param. A blinn_phong root signature is now
`[0] 32BIT_CONSTANTS, [1] CBV b1, [2] SRV t0` plus a static sampler, instead
of five params with two of them permanently unbound. It also gives back a
DWORD of the 64-DWORD budget per duplicated register.

**2. The visibility must be ASSIGNED, never OR-ed.** This is the part a
naive fix gets wrong. In this SDK's Agility 1.616.0 header,
`D3D12_SHADER_VISIBILITY` is a set of **sequential** enumerators, not
bitmasks: `ALL 0`, `VERTEX 1`, `HULL 2`, `DOMAIN 3`, `GEOMETRY 4`, `PIXEL 5`,
`AMP 6`, `MESH 7`. So `VERTEX | PIXEL == 1 | 5 == 5 == PIXEL` -- an OR-based
dedupe silently drops vertex visibility, reproduces the exact original
symptom, **and still builds**, because D3D12 does not validate a table's
visibility against the stages that use it. The fix assigns
`D3D12_SHADER_VISIBILITY_ALL` outright, and the test asserts the OR form is
absent.

Measured, with the vertex stage of `blinn_phong_hlsl.vert` deliberately
reading the b1 cbuffer (the symptom):

| | before | after |
| --- | --- | --- |
| RTX 4060 | vertex read garbage, RT0 wrong | **`[7]`/`[8]` pass, RT0 exactly red** |
| WARP | device lost on the same draw | **12/12 pass** |

The probe shader change was reverted; it was only ever the measurement. What
ships is the backend fix plus a regression test,
`d3d12_root_signature_dedupes_per_stage_tables_with_full_visibility`, which
pins the dedupe, the reused-index bookkeeping for both binding kinds, the
ASSIGN form, and the absence of the OR form. Reverse-verified: switching the
assign back to `|= visibility` turns that test red.

So the whole of the last four entries' mystery is this one defect. WARP was
not the outlier -- it was simply stricter about reading a table that was
never bound.

Two useful things were learned along the way and are worth keeping:

- **`CreateRootSignature` fails with `E_INVALIDARG` when the total root
  signature exceeds 64 DWORDs**, and `D3D12SerializeVersionedRootSignature`
  does not catch it -- the blob serialises fine and only creation rejects it.
  Cost model, measured at the boundary (64 ok, 65 fails): `32BIT_CONSTANTS`
  costs its `Num32BitValues`; each descriptor table costs exactly 1 DWORD
  regardless of how many ranges it holds; static samplers cost 0.
- **`CreateGraphicsPipelineState` fails with `E_INVALIDARG` when a register
  the shader declares is absent from the root signature.** Register
  *visibility* is not checked, which is precisely why the original bug could
  build at all.

### Working the reading list: item 1 answered

`rhi_cmd_bind_texture` and `rhi_cmd_bind_uniform_buffer` **do share a descriptor allocator** — both take from `ctx->cbv_srv_uav_alloc` (`rhi_d3d12.c:3671` and `:3724`), and each returns the slot immediately via `rhi_d3d12_descriptor_give_back(..., ctx->next_fence)`. So the slot a CBV is written to is very likely the slot the next texture bind reuses, overwriting the CBV descriptor before the GPU runs.

That is **not** sufficient to explain the fault, and it is worth saying so rather than leaving it hanging: the passing non-MRT pipeline binds a uniform buffer and a texture in the same order from the same allocator every frame, and its pixel-stage cbuffer read is correct. The overwrite, if it happens, must be harmless there — most likely because the last descriptor written is the one the bound table points at, or because the allocator does not hand the same slot straight back. Which leaves the observation sharp and unexplained: **the same descriptor, same allocator, same order, reads correctly from the pixel stage and not from the vertex stage.**

Item 1 is also not about the temporal buffer lifetime: replacing the destroy-and-recreate of the UBO on every draw with a single buffer plus `rhi_buffer_update` changed nothing (draw 0 still reads back NaN velocity).

The instrumentation from the previous entry has not been run yet and is still the cheapest next move: log `pd->uniform_root_params[1]` and the descriptor handle actually bound, at bind time, on the failing draw. If the vertex stage is resolving a different table than the pixel stage, that prints the difference immediately; if both resolve the same table, the fault is downstream of the root signature entirely.

### Ruled out next: duplicate descriptor tables

The strongest-looking theory left was the per-stage table duplication. The
builder is called once per stage — `VISIBILITY_VERTEX` for the vertex pass,
`VISIBILITY_PIXEL` for the pixel pass — and `rhi_d3d12_root_sig_add_bindings`
has no dedupe, so a register both stages declare emits **two** tables for
the same `(type, register, space)`. `image_root_params` /
`uniform_root_params` keep the **last** index, and nothing binds the other,
so a vertex shader reading such a resource is reading a table that was
never set. That matches the symptom precisely, and it is also a real
DWORD-per-register waste against the 64-DWORD budget R600 spends so
carefully.

Dedupe was implemented (reuse the matching range, union the visibility) and
measured:

- The pre-existing blinn_phong pipelines build with **2 params / 2 ranges /
  1 sampler** instead of 4 tables, and every other D3D12 test still passes.
- **The device loss is unchanged.** A vertex-stage cbuffer read still kills
  it.
- Worse, the MRT PSO then fails: `CreateGraphicsPipelineState` returns
  `E_INVALIDARG` for `NumRenderTargets = 2` with
  `{R8G8B8A8_UNORM, R16G16_SFLOAT}` — a failure that does not occur with the
  same 2-param root signature and the non-MRT shaders, or with 4 tables.

So the duplicate tables are a genuine inefficiency and very likely a real
latent defect, but they are **not** this bug, and the fix is not safe to land
without understanding the `E_INVALIDARG`. Reverted; nothing shipped.

That `E_INVALIDARG` is itself worth a note: two formats, one root signature
shape, and the result depends on how many descriptor tables precede it.
Nobody has characterised that yet, and it is not in scope for R600.

So the outstanding item is a D3D12-backend question, not a shader-authoring
one: **why does a descriptor-bound cbuffer read fault when the shader stage
is VERTEX?** The suspects left are the root-signature side (visibility,
the duplicate per-stage binding merge at `rhi_d3d12_root_sig_add_bindings`,
or `uniform_root_params[1]` resolving to the wrong param) rather than the
buffer itself. The pixel-stage-only path — which is what every current
D3D12 test exercises — cannot see it, which is why the whole suite is
green.

Next entry point is therefore narrow: diff `blinn_phong_mrt_hlsl.*` against
`blinn_phong_hlsl.*` (the only differences are the extra `TEXCOORD3`
varying, the `curr_clip.xy / curr_clip.w` divide in the VS, and the
`SV_Target1` output) and bisect those three. The divide is the first
suspect — nothing else in the pair touches w.

The reverse check on that bind is the useful part: deleting the single
`rhi_cmd_bind_uniform_buffer` line turns the WARP suite red, so the pixel
assertions really are reading the camera out of the CBV. That is the
mechanism step 5 needs; what it does *not* yet cover is the RT1 velocity
attachment, which still has no pixel proof.

### R608 -- skybox / water / terrain, and what is left on GLSL

The five steps closed the *forward* path. Three subsystems the engine draws
every frame were still reading GLSL source through `shader_read_file`, which
on D3D12 means `rhi_shader_create` has no DXIL blob and `rhi_pipeline_create`
rejects it. `render_init` already learned to branch on
`caps.shader_sidecar_paths` (R606); these three call sites are the same shape,
so they branch the same way and request hand-written sidecars.

Nine files: `{skybox,water,terrain}_hlsl.{vert,frag}` plus one
`{...}_mrt_hlsl.frag` each. All three mirror the **GL** variant, not the `_vk`
twin -- D3D12 is not Vulkan, and `terrain.vert` / `water.vert` under
`FORWARD_MRT` *do* declare the `ForwardTemporal` block while their sidecars
deliberately do not.

Three register decisions were forced rather than chosen:

- **No `b1` temporal CBV in the MRT vertex stage.** `terrain_render` and
  `water_render` never call `rhi_cmd_bind_uniform_buffer`, and
  `rhi_cmd_bind_pipeline` does not reset descriptor tables -- a CBV nobody
  binds would read whatever stale table the previous draw left at that root
  parameter. Both sidecars write `velocity = (0,0)`, which is defined *and*
  is what the attachment is cleared to.
- **terrain declares no `t0`.** `terrain.frag` declares `u_albedo` and never
  samples it, so a GLSL compiler drops the inactive binding; the sidecar
  follows. That is also what keeps the pipeline to **one** descriptor table --
  two would clamp the root constants to 248 bytes and drop
  `u_fog_strength@216+4`.
- **terrain declares no `u_model`.** 4 matrices + 5 scalars is 284 bytes,
  past the 64-DWORD budget. terrain's model is the identity on every backend
  (`terrain_vk.vert` omits it for the same reason), so omitting it reproduces
  the transform exactly; `terrain_render`'s model write now resolves -1 and
  is guarded, or every frame would log a dropped-set_uniform for a matrix
  nobody reads.

**No semantic divergence**, and this was checked rather than assumed:
`terrain.frag` declares `u_light_dir` / `u_light_color` / `u_ambient` as GLSL
`const`, so `terrain_render`'s writes to them are *already* no-ops on GL. The
sidecars use `static const` with no `rhi:uniform` marker, so both backends
resolve -1 and behave the same.

**The three pixel proofs are derived, not recorded.** Each expected triple
falls out of the shader algebra in closed form:

| subsystem | setup | closed form | bytes |
| --- | --- | --- | --- |
| skybox | geometry puts `ray.y < 0.01`, so the 24-step cloud march is skipped | `u_sun_color * (scattering + 0.1*horizon_fog) * extinction` | (52, 35, 23) |
| water | plane sits outside the 10..50 fade ramp, so `fade = 0` collapses the fresnel term | `u_water_color * 0.5`, then `* 0.94` submerged | (17,120,115) / (16,113,108) |
| terrain | same uniforms, white vs black shadow atlas | `albedo * (ambient + light_color * 0.808122 * shadow)` | (61,120,30) / (35,70,19) |

The skybox row is the sharpest of the three: its channels *are* the
`RAYLEIGH_COEFF` ratio 5.5 : 13 : 22.4, so a wrong per-channel coefficient or
phase function turns the sky **red** rather than merely darkening it.

Reverse check: changing terrain's shadow constant from `0.4f` to `0.5f` turns
the suite red at the shadowed pixel with (39,79,20) -- which is what
`(61,120,30) -> (35,70,19)` becomes when the 0.4 factor becomes 0.5. Restored
afterwards.

**Then the same suite was run on the RTX 4060 instead of WARP, and that found
a real fragility in the assertions.** Terrain's shadowed blue reads back 18,
not 19. It is not a shader defect: the analytic value is 18.52, i.e. 0.02
above a byte rounding boundary, and the chain contains `sin(10)*sin(20)`, so
fp32 argument reduction alone decides which side it lands on. Every one of
these three expected triples has at least one channel inside 0.08 of a
boundary -- terrain 60.57 and 18.52, water 16.575, skybox 52.44 -- because
they were all picked to land on round byte values. `warp_expect_rgba` now
takes a per-channel tolerance and all three colour assertions pass 1. The
velocity assertions stay exact, because 0.0 is a literal and has no boundary
to fall across. The reverse check still fires under that bound: 0.4 -> 0.5
moves red by 4 and green by 9.

Hardware result after the fix: **16/17**. The one failure is
`warp_device_identity_is_honest`, which asserts the adapter *is* WARP and is
therefore supposed to fail when someone unsets `ENGINE_D3D12_WARP`. This is
the first time the D3D12 pixel proofs have run on real silicon.

Two arithmetic errors were in the *test comments* (the assertions were always
right): terrain's `pattern` is -0.01490 not -0.02498, and skybox's
`horizon_fog` is 0.0755 not 0 -- where the sky's dominant red contribution
comes from.

Gates: D3D12 `ctest -LE "graphics|fuzz"` 171/172 and `ctest -L graphics` 8/8,
WARP 17/17; VK 170/171 with 0 validation messages and golden MAE unchanged at
28.75 / 13.54; GL 169/170 with golden MAE unchanged at 15.60 / 1.15. The one
failure in all three trees is `test_platform_win32_runtime`'s
`FAIL: OpenClipboard failed`, which unmodified HEAD also fails.

**What is still GLSL-only on D3D12.** The test for this is not "which shaders
exist" but "which call sites branch on `caps.shader_sidecar_paths`". There are
**six**, in the whole repository: `main.c:421`, `main.c:495`, `main.c:533`,
`skybox.c:24`, `terrain.c:142`, `water.c:35`. Everything else calls
`shader_read_file` + `rhi_shader_create` unconditionally, so it fails to
compile on D3D12 and degrades through whatever warning its own subsystem
already prints:

- `main.c`: the clustered family (`pbr_clustered` / `_inst` / `_skin` /
  `_arr`), deferred (gbuffer / gbuffer_arr / deferred_light), `depth_only`,
  `instanced`, `skinned`. R610 removed the hot-reload pipeline from this list
  (it was the one at `main.c:2940`); what remains there is those six.
- `src/renderer/` (one vert/frag pair each): `cinematic`, `color_grade`,
  `combined_post_process`, `contact_shadow`, `debug_viz`, `deferred`, `dof`,
  `forward_velocity`, `fxaa`, `god_rays`, `lens_effects`, `lens_flare`,
  `motion_blur`, `point_shadow`, `post_process`, `sharpen`, `ssao`, `ssgi`,
  `ssr`, `sss`, `taa`, `tonemap`, `upscale`, `volumetric`.
- compute: `gpucull.c` (`cull.comp` / `unified_cull.comp`), `lighting.c`
  (`cluster_cull.comp`), `particles.c` (`particle_update.comp` /
  `particle_cull.comp` / `particle.{vert,frag}`), `ibl.c`,
  `indirect_draw.c`, `occlusion_cull.c`.

`indirect_draw.c` deserves its own line, because it is the one that decides
whether the material-array path runs at all on D3D12. Two independent
fail-closed gates, both currently closed:

1. `rhi_d3d12.c` never sets `caps.indirect_draw_supported` -- only
   `rhi_gl.c:770` and `rhi_vk.c:1852` do, and `RHIDevice` is `calloc`'d --
   so `indirect_draw_init` bails with "backend reports no indirect draw
   support".
2. Even with the flag set, `id_load_compute` reads `compact_draws.comp`
   through `shader_read_file`, which is GLSL, so the compaction pipeline is
   invalid and `indirect_draw_init` destroys the system and returns false.

R607 therefore landed the array sidecar and the 2D array texture support for
a path that cannot execute on this backend yet. Enabling it needs a compute
sidecar for `compact_draws.comp` -- and `rhi_shader_create_compute`'s own
D3D12 support is unverified -- plus the layer fix from R609.

The `shader_read_file` calls in `test_vulkan.c` are test fixtures and are not
in this list.

**Unresolved and not independently re-verified here:** the D3D12 demo still
exits with `D3D12 device removed: 0x887a0005` (`DXGI_ERROR_DEVICE_HUNG`). A/B
suggests it predates these three subsystems, but it correlates closely with
the fallback list above and deserves its own pass.

Still open from R607, unchanged: the production array layer comes from
`first_instance` (indirect `StartInstanceLocation`), which WARP discards. It
needs a real GPU running `rhi_cmd_draw_indirect` to close.

### R609 -- the real GPU says the layer never reaches the shader, but nothing renders wrong today

The line above was wrong. Running the suite on the RTX 4060 closes the open
item, and the answer is not "WARP drops it". **D3D12 drops it.**

```
{InstanceCount = 1, StartInstanceLocation = 1} -> layer 0
{InstanceCount = 1, StartInstanceLocation = 2} -> layer 0
{InstanceCount = 2, StartInstanceLocation = 2} -> last instance is layer 1
```

The third record is the discriminating one. `InstanceCount` *is* honoured --
two instances rasterise and the second wins -- so the argument buffer is
genuinely being read, and a layer of 0 in the first two rows can only be the
base being dropped rather than an upload that never landed. The per-draw
argument buffer is read back and asserted too, so "the record on the CPU was
correct" is recorded evidence rather than an assumption.

**The cause.** `blinn_phong_arr.vert` reads `uint(gl_BaseInstanceARB)` --
the indirect record's `first_instance`, independent of `InstanceCount`. The
D3D12 sidecar reads `SV_InstanceID`, which is `gl_InstanceID`: base plus
instance index. The R607 sidecar comment asserted the two were "that same
system value"; they are not. They agree only when `first_instance` is 0,
which is the opposite of what production draws:

- `main.c:3779` -- `cmds[cidx].instance_count = 1`
- `main.c:3947` -- `cmds[ci].first_instance = group_layer[mg]`

**Correction to how severe that is.** The first version of this entry said
"every material-array mesh on D3D12 samples layer 0". That overstated it.
`rhi_d3d12.c` never sets `caps.indirect_draw_supported` (only `rhi_gl.c:770`
and `rhi_vk.c:1852` do), so `indirect_draw_init` fail-closes with "backend
reports no indirect draw support", `mb->array_system_ready` stays false, and
`mega_mat_arrays_draw` returns 0 at its first line. The array pipeline is
created and never drawn.

So this is a **trapdoor under a disabled subsystem**, not a live rendering
bug. It becomes one the moment indirect draw is enabled on D3D12, and it
would not announce itself: every mesh keeps shading correctly, just always
with material layer 0. Which is also a fair summary of where R607 left the
array work -- built and unexercised end to end on this backend.

**There is no semantic that fixes this.** `SV_StartInstanceLocation` is the
right one and dxc rejects it at every shader model from `ps_6_0` to
`ps_6_11`, in both stages:

```
error: invalid semantic 'SV_StartInstanceLocation' for shader model: vs
error: invalid semantic 'SV_StartInstanceLocation' for ps 6.0
```

The bare name `StartInstanceLocation` *does* compile, which is the trap:
`-dumpbin` shows it as a plain user semantic with `SysValue = NONE` and its
own register, i.e. nothing the runtime populates. Wiring that in would look
fixed and read garbage.

**The fix is the mechanism D3D12 provides for exactly this**: a command
signature carrying a second `D3D12_INDIRECT_ARGUMENT_TYPE_CONSTANT`
argument, which copies a value out of the argument buffer and into a root
constant the shader can read. Room exists -- this pipeline's push block ends
at 240 and two descriptor tables clamp `32BIT_CONSTANTS` at 62 DWORDs = 248
bytes, so `uint u_layer` at 240 fits without a new root parameter.

The blast radius is larger than it first looked. `indirect_draw_execute`
dispatches records from `visible_draws_buf`, which is filled by a **GPU
compute pass** that compacts and scatters whole `DrawIndexedIndirectCmd`
entries, and that compute shader is GLSL-only on D3D12. So the fix has to
land together across: the command signature, the compute compaction shader's
own struct layout, the indirect-argument ABI, and the sidecar. It is
**recorded, not attempted blind**.

The sidecars keep reading `SV_InstanceID` -- unchanged behaviour -- and
`indirect_start_instance_does_not_reach_sv_instance_id` pins all three
measured rows. When the path is enabled that test goes red, which is the
point: the fix has to be a deliberate update, not a silent change of meaning
inside a passing test.

Hardware result: **17/18**. The one failure is `warp_device_identity_is_honest`,
which asserts the adapter *is* WARP and is meant to fail when
`ENGINE_D3D12_WARP` is unset.
