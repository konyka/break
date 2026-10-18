# D3D12 FORWARD_MRT velocity / RT1 output — design

Status: design only, not implemented
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
