# Cross-Engine Inventory Stage 1 Design

## Scope

Create five evidence-first documents under `docs/cross_engine/`:

- `cryengine_inventory.md`
- `bw191_inventory.md`
- `unreal_inventory.md`
- `feature_matrix.md`
- `missing_capabilities.md`

The documents compare 17 modules: module system; ECS/entity; world/scene; tasks; threads/messages; networking; UI/input; rendering/RHI; physics; audio; assets/hot reload; editor; diagnostics/remote debugging; crash upload; online update; security/anti-cheat; and large-world/streaming.

## Evidence Policy

- Break status uses current repository evidence: source paths, CMake target boundaries, tests, and `docs/Implementation_Status.md` / `docs/Architecture_Overview.md`.
- External engine entries use publicly identifiable architecture/source/documentation references available in the repository or cited URLs. Unknown details are marked `资料不足`, not inferred.
- `已实现` means implemented and evidenced in the relevant runtime target. Focused/test-only APIs are marked separately from formal engine/demo integration.
- This stage creates documentation only. It does not implement engine features or change CMake/source behavior.

## File Responsibilities

### Engine inventories

Each engine inventory has the same 17-module section order. Every section contains: scope, known capabilities, evidence/source reference, and comparison notes relevant to Break.

### Feature matrix

A compact matrix uses the same 17 rows and four engine columns. Each cell has a status and a short evidence pointer. A legend defines status terms and the distinction between documentation and implementation.

### Missing capabilities

Groups gaps into: documentation delivered by Stage 1; Break foundations already present; focused/test-only boundaries; formal runtime integration gaps; product systems not implemented. Each gap includes impact and a suggested later phase, without claiming delivery.

## Validation

- All five files exist under the exact requested paths.
- Every file covers or links to all 17 modules.
- Status terms and evidence policy are consistent across files.
- Cross-file links resolve to repository paths.
- `git diff --check` passes.
