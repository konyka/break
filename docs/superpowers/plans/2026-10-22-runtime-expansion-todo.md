# Runtime Expansion Todo / Master Plan

> Status ledger for the requested multi-stage work. Each subproject must get its own design/spec, implementation plan, tests, review, and evidence before being marked complete.

## Stage 1 — Cross-engine inventory

- [x] `docs/cross_engine/cryengine_inventory.md`
- [x] `docs/cross_engine/bw191_inventory.md`
- [x] `docs/cross_engine/unreal_inventory.md`
- [x] `docs/cross_engine/feature_matrix.md`
- [x] `docs/cross_engine/missing_capabilities.md`
- [x] Evidence policy and 17-module coverage validated

## Stage 2 — Runtime design

> 设计已完成，实施计划为 `docs/superpowers/plans/2026-10-22-runtime-core-formalization.md`。Lua boundary、Runtime Core formal facade、Asset/HotReload contracts 仍是设计目标，尚未实现。

- [x] `runtime_overview.md`
- [x] `runtime_thread_model.md`
- [x] `runtime_message_model.md`
- [x] `runtime_network.md`
- [x] `runtime_asset_streaming.md`
- [x] `runtime_hot_reload.md`
- [x] `runtime_security.md`
- [x] Review formal-vs-focused CMake target boundaries
- [x] Review unified Runtime Core contract: coordinator lifecycle, local subsystem mappings, compatibility-vs-formal API behavior, capacities/backpressure, and `BreakRuntimeError`
- [x] Review Lua boundary and Asset/HotReload state/result contract; Stage 2 remains design goal/not implemented
- [x] Review opaque `u64` request handles, generation checks, owned `BreakAssetCompletion`/`BreakReloadCompletion`, explicit completion/request release, and poll/commit/cancel result enums
- [x] User approval of Stage 2 design in auto execution mode
- [x] Keep all Stage 2 lifecycle/backpressure/Lua/type/error/Asset-HotReload contracts marked design target/unimplemented
- [x] Create `docs/superpowers/plans/2026-10-22-runtime-core-formalization.md`

## Stage 3 — Lua runtime

- [ ] Design `BreakLuaRuntime` opaque C11 facade
- [ ] Define module load/reload/version/error contracts
- [ ] Define bounded ECS batch/command bindings
- [ ] Add normal/ASan/TSan RED/GREEN tests
- [ ] Implement production target and docs
- [ ] Review LuaJIT as optional backend only after baseline

## Stage 4 — Scene editor

- [ ] Design editor shell and command routing
- [ ] World outliner/entity inspector
- [ ] Property transactions and undo/redo
- [ ] Asset browser and hot reload
- [ ] Viewport/gizmo/scene round-trip
- [ ] Console/profiler/network/render panels
- [ ] Editor smoke and native UI evidence

## Stage 5 — Online update/crash/security

- [ ] Signed manifest/content-addressed package design
- [ ] Download/resume/A-B/rollback implementation plan
- [ ] Crash context/spool/upload/symbolization design
- [ ] Authentication/replay/rate-limit threat model
- [ ] Anti-cheat trust-boundary design
- [ ] Security review and release configuration tests

## Stage 6 — Graphics API lifecycle

- [ ] Audit existing Vulkan/D3D12/Metal/headless plans
- [ ] Complete backend-specific remaining gaps in separate plans
- [ ] Collect per-backend evidence
- [ ] Maintain OpenGL deprecation/removal gate

## Cross-cutting validation

- [ ] Clean normal build with all relevant targets explicitly built
- [ ] Clean ASan/UBSan build and relevant tests
- [ ] Clean TSan build and relevant tests
- [ ] Explicitly build/run all fuzz smoke targets
- [ ] Native/CI cross-platform evidence recorded
- [ ] Full CTest failures classified as code vs environment vs not-built
- [ ] `git diff --check`
- [ ] 文档自审：生命周期、shutdown 顺序、错误类别、容量/背压、Lua boundary、Asset/HotReload 状态机前后一致
- [ ] Final independent code review
