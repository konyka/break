# ECS Snapshot, Replication and AoI Implementation Plan

> **For agentic workers:** REQUIRED SUB-SKILL: Use superpowers:subagent-driven-development (recommended) or superpowers:executing-plans to implement this plan task-by-task. Steps use checkbox (`- [ ]`) syntax for tracking.

**Goal:** Add immutable C11 World snapshots, snapshot deltas, and per-connection AoI scope computation above the existing ECS and Snowflake session/adapter layers.

**Architecture:** GameThread remains the sole mutable World owner. A structural barrier produces a deep-copied canonical snapshot with generation-aware entity identity. Pure snapshot diff produces deltas; an independent spatial index and Witness policy produce `enter/stay/leave`; only fully validated messages reach the GameThread mutation phase.

**Tech Stack:** C11, existing ECS/TaskSystem/Scene serialization, BreakNetAdapter/Snowflake, CMake/CTest, ASan/TSan.

## Global Constraints

- No mutable `World *`, `Archetype *`, `Chunk *`, or RHI handle crosses into network workers.
- Network callbacks never mutate ECS/World/Lua/UI/RHI.
- Snapshot identity includes `(index,generation)`; use a separate NetEntityId only if later requirements require cross-World persistence.
- Component bytes are replicated only for registered deterministic POD schemas; pointer/resource/cache components need explicit policy.
- Deltas are computed only between immutable snapshots.
- Delta base/schema mismatch rejects before World mutation.
- Existing transform replication remains intact until replacement tests pass.
- Every behavior follows RED→GREEN→REFACTOR.

---

## Task 1: Red tests and schema contract

**Files:**
- Create: `engine/tests/test_ecs_replication.c`
- Inspect: `engine/src/ecs/ecs.h`, `ecs_system.h`, `test_ecs.c`, `test_ecs_system.c`, `test_scene_serial.c`
- Modify: `engine/CMakeLists.txt`

- [ ] Add failing tests for generation-aware snapshot identity, deep-copy immutability, deterministic ordering/hash, schema registration, and unsupported component policy.
- [ ] Add failing tests for delta create/destroy/add/remove/update and base mismatch.
- [ ] Add failing tests for AoI enter/stay/leave and spatial boundary behavior.
- [ ] Register the test target and run it red for missing APIs.

## Task 2: Component schema registry

**Files:**
- Create: `engine/src/ecs/replication_schema.h`
- Create: `engine/src/ecs/replication_schema.c`
- Modify: CMake/tests

- [ ] Define opaque registry and schema record with component ID, version, size, flags, and optional encode/decode callbacks.
- [ ] Reject duplicate IDs, zero sizes, invalid alignment, and unsupported pointer-containing raw-byte policy.
- [ ] Add deterministic registration/lookup/hash tests.
- [ ] Keep registry GameThread/initialization-only; do not add a mutex to ECS hot paths.

## Task 3: Immutable WorldSnapshot

**Files:**
- Create: `engine/src/ecs/world_snapshot.h`
- Create: `engine/src/ecs/world_snapshot.c`
- Modify: CMake/tests

- [ ] Implement a deep-copied snapshot containing tick, snapshot ID, schema hash, sorted full Entity handles, component records, and owned bytes.
- [ ] Wait for/require the existing ECS structural barrier; do not enumerate while structural mutation is active.
- [ ] Never store internal World/archetype/chunk pointers in the snapshot.
- [ ] Add refcounted lifetime and mutex-protected acquire/release publication.
- [ ] Test reader lifetime, mutation after build, stale generation, deterministic ordering, and snapshot hash.

## Task 4: Pure snapshot delta

**Files:**
- Create: `engine/src/ecs/world_delta.h`
- Create: `engine/src/ecs/world_delta.c`
- Modify: CMake/tests

- [ ] Diff two immutable snapshots into entity create/destroy and component add/remove/update records.
- [ ] Include base ID, target ID, schema hash, tick, and deterministic record order.
- [ ] Reject base/schema mismatch during apply before mutating World.
- [ ] Apply deltas only on GameThread and only through existing World APIs.
- [ ] Test index reuse with generation change, idempotence, malformed record, and rollback on apply failure.

## Task 5: Spatial index, Witness, and AoI

**Files:**
- Create: `engine/src/network/break_aoi.h`
- Create: `engine/src/network/break_aoi.c`
- Modify: CMake/tests

- [x] Define Witness, replication object, simple grid/spatial index, and connection scope records.
- [ ] Build candidates from object positions and witness radius/shape.
- [ ] Apply basic flags for always-relevant, owner-only, and dormant.
- [ ] Return sorted enter/stay/leave sets with hysteresis configuration.
- [ ] Test radius boundary, multiple witnesses union, leave/enter, priority, and deterministic ordering.

## Task 6: Replication scheduling and adapter integration

**Files:**
- Create: `engine/src/network/break_replication.h/c`
- Modify: `engine/src/network/break_net_adapter.h/c` only where the existing send API is consumed
- Modify: CMake/tests

- [ ] Register Real objects and per-connection Ghost/scope state.
- [ ] Build baseline for enter, dirty delta for stay, destroy/dormant for leave.
- [ ] Enforce per-connection bandwidth and object priority without blocking GameThread.
- [x] Convert complete replication messages to existing BreakNet outbound queue; do not call Snowflake directly from World code.
- [ ] Test scope transitions, baseline retry, queue overload, and disconnect cleanup.

## Task 7: Fragmentation and validation

**Files:**
- Create: `engine/src/network/break_replication_fragment.h/c`
- Modify: tests/CMake

- [ ] Fragment deltas under the existing transport limit.
- [x] Reassemble by delta ID/base ID/fragment index/count/checksum.
- [x] Reject duplicate/conflicting fragments and base mismatch.
- [x] Apply only after all fragments validate; test loss, reorder, duplicate, and retry.

## Task 8: Documentation and validation

**Files:**
- Create: `docs/design/ecs_snapshot_replication_aoi.md`
- Modify: `docs/Architecture_Overview.md`
- Modify: `docs/Implementation_Status.md`

- [x] Document World mutation/snapshot phases, schema rules, Real/Ghost/Witness/AoI, delta lifecycle, thread ownership, and fragmentation.
- [x] Add Mermaid diagrams for snapshot publication, delta application, AoI enter/stay/leave, and network thread/GameThread boundaries.
- [x] Run normal, ASan, and TSan focused tests (fragment 7/7; Snowflake replication 7/7 in each lane).
- [x] Run full CTest and record unrelated failures exactly; the latest 181-test tree is incomplete because five fuzz executables were not built, so those entries are `Not Run`.
- [x] Run `git diff --check`.

## Completion Gate

This plan is complete only when snapshot/delta/AoI tests pass under supported sanitizer lanes, existing ECS/Scene/network tests remain green, replication messages go through BreakNetAdapter rather than direct sockets, and documentation explicitly distinguishes implemented behavior from future authority handoff, prediction, distributed Cell services, Lua integration, editor tooling, online updates, and security.
