# Graphics Backend Audit (Stage 6, subproject 1)

Date: 2026-10-25. Repo state: `master` at `e804f54b`. Scope: audit of the existing RHI plans (`docs/superpowers/plans/2026-10-14-rhi-plan-{a..f}-*.md`, `2026-10-18-d3d12-mrt-fbo-design-plan.md`) against code, tests, CI and recorded evidence. This is a read-only audit: no backend code changed.

Evidence key: **(a)** implemented and tested in this repo; **(b)** implemented, no evidence run here; **(c)** planned only; **(d)** not found.

Method: three independent read-only audits (Vulkan + headless; D3D12 + Metal; OpenGL removal gate + release policy + evidence tooling). The claims that drive the gaps below were re-checked directly on the tree: the missing gate script, migration notice, signoff doc and tags; the missing deprecation mechanism; the `auto` selector resolution; and the `windows-d3d12.yml` run history. Items marked "reported" were not re-derived.

Not verified by this audit: no graphics, Metal or D3D12 test was run; CI artifacts were not downloaded; `test_rhi_backend_selection` (nested configures) was not run; plans A-D and `rhi_metal_notes.md` were not read in full.

## 1. Per-backend status

| Backend | Status | Evidence on record | Weakest link |
|---|---|---|---|
| Headless | (a) | `engine_rhi_headless` always built; fail-closed (`rhi_headless.c:1`: never GPU evidence); ~27 `headless` ctest tests in a Vulkan tree | By design not a rendering backend |
| Vulkan | (a) | `lane-validation-linux-vk` (VUID grep gate), `lane-gpu-runtime-linux-vk`, `lane-native-surface-wayland`; committed Windows Vulkan receipt | CI GPU evidence is lavapipe (software); Steam Deck lane skipped (`ENABLE_GPU_LANES` unset); Android/iOS only COMPILED |
| D3D12 | (a) with caveats | Committed Windows receipt (RTX 4060, ratio 1.222); WARP lane; 12/12 D3D12 tests recorded in `Implementation_Status.md` | Benchmark workload is the swapchain clear/present harness, not the engine scene; `windows-d3d12.yml` red on master (see §3); MRT/FBO cubemap paths unimplemented |
| Metal | (a) with caveats | Committed M2 receipts (Metal + MoltenVK, BENCHMARK_COMPARABLE) | iOS has no device evidence (COMPILED); `indirect_count`, GPU timer, texture arrays and several bind paths are stubs/fail-closed |
| OpenGL | (a), deprecated in prose only | `lane-gpu-runtime-linux-gl`, `wayland-gl` (software GL) | No code-level deprecation mechanism (see §2); remains the `auto` default on Linux |

## 2. OpenGL removal gate and deprecation mechanism

The 11-condition gate is text in `docs/superpowers/specs/2026-10-14-multi-backend-rhi-design.md:153-165`. Its executable form was never created.

| Item | Status | Verified |
|---|---|---|
| `engine/tests/test_opengl_removal_gate.cmake` | (c) plan text only (plan F Task 6) | file absent |
| `docs/rhi_opengl_removal_migration.md` (cond. 9) | (c) | file absent |
| `docs/rhi_opengl_removal_signoff.md` (cond. 11) | (c), needs a human APPROVED | file absent |
| Signed rollback tag (cond. 10) | (d) | `git tag -l` returns 0 tags; `rollback-drill.yml` exists but was reported as never run |
| ACTIVE / DEPRECATED / REMOVED state per backend | (d) | no state enum; the only `DEPRECATED` hits are an unrelated uniform-location API comment (`rhi.h:623`) |
| Compile-time diagnostic when selecting OpenGL | (d) | `engine/CMakeLists.txt:164-200` resolves `opengl`/`auto` with no `DEPRECATION`/`WARNING` message |
| One-time runtime migration warning | (d) | GL emits only an INFO `RHIEVT` `compat-override` line (`rhi_rollout.c:74`, `rhi.c:11-19`); not a warning, not once, no migration text (reported) |
| CI migration check / config migration tool | (d) | the closest test, `test_rhi_opengl_compat_fallback_contract`, requires `opengl` to remain in the chain, the opposite of a removal check |
| Rollout config `allowed` / `fallback_chain` consumed at runtime | (d) | only the `config_version` is baked at compile time; nothing reads the chain (reported) |

Selector behaviour: `auto` resolves to `opengl` unless `ENGINE_VULKAN`, Metal or Windows D3D12 is selected (`engine/CMakeLists.txt:186-197`). The rollout JSON says Linux should prefer Vulkan, and the code does not do that. Any "deprecated" claim is therefore currently unsupported by the build: a default Linux build selects OpenGL with no diagnostic.

Gate conditions (from the audit; conds. 4-5 were hand-checked, not gate-script-checked):

| Cond. | Content | State |
|---|---|---|
| 1 | Android / Linux / Steam Vulkan GPU_RUNTIME + BENCHMARK_COMPARABLE | **not met** (Android COMPILED; Linux lavapipe only; Steam Deck skipped) |
| 2 | Native Metal GPU_RUNTIME on macOS and iOS | **partial** (macOS M2 receipt; iOS COMPILED only) |
| 3 | Windows D3D12 GPU_RUNTIME + BENCHMARK_COMPARABLE | met with caveats (swapchain harness, validation-off comparison; reported ratio ~0.80 with validation on) |
| 4-5 | Renderer/UI and production consumers free of GL | hand-checked only (`test_renderer_backend_token_gate` passes with 5 whitelisted hits) |
| 6-8 | GL artifacts removed; clean-room build without GL; all consumers link/start | not started (`rhi_gl.c` still built and linked) |
| 9 | Migration notice published | **not met** (file absent) |
| 10 | Signed rollback tag | **not met** (no tags) |
| 11 | Signoff | **not met** (file absent) |

Conclusion: OpenGL removal must not be scheduled. Four conditions are unmet or absent outright, and the marking mechanism the request asked for (ACTIVE/DEPRECATED/REMOVED with compile-time and one-time runtime diagnostics, CI check, migration tool) does not exist anywhere in code.

## 3. Findings that need action

Ordered by how much they distort the picture of Stage 6 today.

1. **`windows-d3d12.yml` is failing on master.** Verified with `gh run list` and `gh run view --log-failed`: run 40184056098 (R698 docs revalidation) and 40182884566 (R697, Agility SDK 1.616.0 to 1.619.6) both failed; 40169314427 succeeded. In run 40184056098 the job's only failed step is "WARP push-constant write-drop gate". `test_d3d12_warp_runtime` itself reported `Passed` (74 s). The step fails because its grep for the string `outside declared` in the verbose test log matched, which the workflow comments describe as "a push-constant write was dropped as outside the pipeline's declared range; the WARP suite passes anyway, so this grep is the only detector". The string comes from two `LOG_WARN` drops in `engine/src/rhi/rhi_d3d12.c`: `set_uniform ... outside declared` (line 3495) and `push_constants ... outside declared ... (or unaligned)` (line 3545). The matching log line itself is not in the retained CI log (only the step command is), so which call dropped a write is unknown. Reproducing needs a Windows run of `ctest -R test_d3d12_warp_runtime -V`. R697 also bumped the Agility pin, so the pin note in `rhi_backend_evidence.md:60` (1.616.0) may be stale. D3D12 evidence recorded as green should be treated as unconfirmed until this is triaged: the likely cause is a real dropped push-constant write that the pixel tests do not catch, not a flaky runner, but that is a hypothesis, not a finding.
2. **Plan files cannot be used as a progress source.** Plan F has 0 checked and 69 unchecked boxes, while the evidence ledger (`rhi_backend_evidence.md`) reports its Tasks 0-5 and 7-10 as complete. Plans A-F show no ticked boxes at all. The ledger is the authority; the plan files are not.
3. **No deprecation mechanism exists, but docs and README call OpenGL "deprecated".** Closing this needs a new task, not an existing plan task (plan F Task 5 delivered only the INFO-level `compat-override` event and a whitelist scan).
4. **`auto` selects OpenGL on Linux**, contradicting the rollout JSON preference. A decision is needed before deprecation is meaningful.
5. **Rollback mechanism described in the runbook is not wired.** The runbook describes patching the fallback order; the code only bakes a config version.
6. **D3D12 consumer parity is incomplete.** `engine_demo` was reported blocked on HLSL sidecars beyond the blit/myui allowlist, and the ledger text on this is partly stale after `rhi_device_create_compiled` (commit `90d3c068`). Condition 8 cannot pass on D3D12 until this is settled.
7. **Receipt validator is weaker than its schema doc.** It checks presence and non-empty fields (plus the four metrics for BENCHMARK_COMPARABLE) but not enums, the 40-char commit or `build_config`. The schema's "known alignment items" (`rhi_benchmark_receipt_schema.md:56-64`) are still open.
8. **CI receipts are artifacts with 90-day retention; only 4 receipts are committed** (`docs/receipts/`: macOS Metal, macOS MoltenVK, Windows D3D12, Windows Vulkan). For the ledger to stay verifiable, a harvest step or a committed index is needed.
9. **Doc drift.** `Implementation_Status.md` and `Rendering_Pipeline.md` describe an OpenGL 4.5 + Vulkan dual backend and omit Metal, D3D12 and deprecation. Docs/code mismatch noted by the Vulkan audit: `vulkan_support_matrix.md:10` says dynamic rendering / synchronization2 are "probe only", while `rhi_vk.c:1829` sets the capability bits (they are consumed through caps). The runbook names expiry "v2.0.0 + 30 days", and no v2.0.0 work exists.

## 4. Remaining gaps by owner

Where an owning plan exists it is named; "new" means no plan covers it.

| # | Gap | Owner |
|---|---|---|
| 1 | iOS x Metal real-device GPU_RUNTIME receipt | plan C Task 15 / plan F Task 6 unlock; needs a device |
| 2 | Android x Vulkan runtime evidence | new (no task found); needs a device |
| 3 | Real-GPU Linux / Steam Deck Vulkan benchmark | plan F Task 7; needs a self-hosted runner and `ENABLE_GPU_LANES` |
| 4 | `test_opengl_removal_gate.cmake`; its Android/Steam regexes do not match current ledger rows | plan F Task 6 |
| 5 | Migration notice and signoff documents | plan F Task 6; signoff needs a human |
| 6 | Signed `v1.x` tag and a first rollback drill | plan F Task 9; maintainer action |
| 7 | Deprecation marking mechanism (state enum, CMake diagnostic, one-time runtime WARN with migration text, CI check, config migration tool) | new |
| 8 | Decide `auto` default on Linux (Vulkan vs OpenGL) | new decision, touches plan F Tasks 3 and 5 |
| 9 | Make rollout `allowed` / `fallback_chain` live, or correct the runbook | plan F Task 3 follow-up |
| 10 | Triage the `windows-d3d12.yml` regression and re-record D3D12 evidence | new, plan D follow-up |
| 11 | D3D12 consumer parity (`engine_demo` HLSL sidecars, FBO/bindings) | new, referenced at `rhi_backend_evidence.md:211` |
| 12 | D3D12 cubemap FBO paths | `2026-10-18-d3d12-mrt-fbo-design-plan.md` Task 5 |
| 13 | Metal stubs: `indirect_count`, GPU timer, `texture_array_create`, `cmd_bind_texel_buffers`, `cmd_bind_material_textures_ibl`, `cmd_bind_deferred_gbuf_textures`, `cmd_bind_image_texture` | plan C Tasks 9, 14, 15 |
| 14 | Receipt validator hardening and schema alignment items | plan F Task 7 |
| 15 | Committed index or harvest step for CI receipts | plan F Task 8 follow-up |
| 16 | Hi-Z `{0,0}`/`{1,1}` on NVIDIA remains environment-only; `TV_ONLY` gates retained | plan E follow-up (reported) |
| 17 | Doc drift in `Implementation_Status.md` / `Rendering_Pipeline.md`; plan-file status hygiene | docs task |

## 5. What this audit does not claim

- No capability claim is raised or lowered here. Evidence levels in `rhi_backend_evidence.md` stay as recorded, except that D3D12 should be read as unconfirmed while finding 1 is open.
- A runtime-feature milestone (Stages 1-5) is not graphics evidence, and nothing here converts one into the other.
- Gaps 1, 2, 3 and 6 need hardware or maintainer actions that cannot be done from this repo alone.
