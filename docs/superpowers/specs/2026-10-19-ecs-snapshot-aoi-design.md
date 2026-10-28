# ECS Snapshot, Replication and AoI Design

**Status:** Design approved for staged implementation after Session/Protocol phase.

## Goal

Add a C11, GameThread-owned replication model that produces immutable World snapshots, computes deltas between snapshots, and derives per-connection `enter/stay/leave` scopes without exposing mutable ECS or Scene pointers to Snowflake/network workers.

## Existing Constraints

- ECS entity identity is `(index, generation)`; `chunk_get_entity()` alone is not a valid network identity because it lacks generation.
- ECS archetype/chunk/query pointers are mutable and invalid across structural mutation.
- Scene serialization currently stores raw component bytes and asset references but does not provide an immutable concurrent snapshot.
- Existing `NetTransformSnapshot` is only `entity_id + position[3]`; it is not a general replication model.
- Existing peer `delta.log` stores peer statistics, not ECS deltas.
- Snowflake callbacks produce immutable events; GameThread owns sessions, World, ECS, and Lua.

## Architecture

```text
GameThread mutable World
    |
    | structural barrier + completed worker tasks
    v
WorldSnapshot builder
    |
    +-- deep copy Entity(index,generation)
    +-- component schema encode
    +-- stable sorting and hash
    +-- immutable resource GUID/URI references
    v
Published Snapshot (refcounted)
    |                         |
    v                         v
Delta diff                 AoI/Replication scheduler
(base,new)                 (Witness + spatial index + policy)
    |                         |
    v                         v
Fragmented replication messages
    |
BreakNetAdapter outbound queue
    |
Snowflake reactor
```

## Immutable Snapshot

A snapshot owns all memory and contains no `World *`, `Archetype *`, `Chunk *`, RHI handle, or mutable Scene pointer. It contains:

- world ID;
- tick;
- snapshot ID;
- schema hash;
- sorted entity records with full `(index,generation)` identity;
- sorted component records and copied bytes;
- stable resource GUID/URI references only.

Publication uses an atomic current pointer plus a mutex-protected acquire/release operation to prevent load-retain-free races. The first implementation uses a mutex-protected refcount; epoch/hazard reclamation is a later optimization, not a prerequisite.

Snapshot construction occurs only after parallel ECS systems complete and structural mutation is blocked. Snapshot enumeration is canonical: entity key ascending, component type ascending, component entity records ascending.

## Component Schema

The existing `ComponentType -> size` registry is insufficient for cross-machine replication. Replicated component definitions must declare:

- component ID;
- schema version;
- size/alignment;
- snapshot/encode/decode policy;
- replication flags;
- runtime-only/resource-reference/pointer-containing classification;
- optional quantization and custom delta functions.

Raw bytes are allowed only for deterministic POD components with a declared wire representation. Pointer-containing, derived/cache, and RHI-backed components are excluded or use custom serializers.

## Delta

A delta is a pure value diff between two immutable snapshots:

- base snapshot ID;
- target snapshot ID;
- schema hash;
- tick/sequence;
- entity creates;
- entity destroys;
- component adds;
- component removes;
- component updates.

Applying a delta is GameThread-only. A base mismatch or schema mismatch rejects the delta and requests a full snapshot. Repeated application of the same delta is idempotent by target snapshot ID.

Because the existing transport MTU is bounded, a WorldDelta is fragmented with delta ID, base ID, fragment index/count, checksum, and sequence. Fragments are reassembled before any World mutation.

## Real/Ghost/Witness/AoI

- **Real:** registered authoritative replication object with stable ID, authority, spatial cell, version, dirty state, and schema.
- **Ghost:** per-connection replica state, never authoritative and never shared between connections.
- **Witness:** one or more per-connection interest sources containing position, direction, velocity, shape/radius, and priority.
- **AoI:** connection-specific scope after spatial candidates, permissions, data-layer filters, relevancy, and bandwidth policy.

AoI computation returns explicit sets:

```text
enter = new_scope - old_scope
stay  = new_scope ∩ old_scope
leave = old_scope - new_scope
```

`enter` sends a baseline, `stay` sends dirty updates subject to priority/budget, and `leave` sends destroy or dormant according to policy. Authority handoff is separate from client AoI membership.

## Thread Contract

- Network/reactor threads parse and reassemble bounded immutable messages only.
- Network threads never call `world_create_entity`, `world_destroy_entity`, component mutation, Lua, UI, or RHI.
- GameThread applies validated deltas at the World mutation phase.
- Snapshot readers never access mutable ECS chunks.
- Asset workers produce independent results; GameThread commits Scene/ECS changes.
- Snapshot build waits for existing ECS parallel systems and disallows structural mutation during enumeration.

## C11 API Direction

The implementation will introduce opaque types and stable C11 handles; exact signatures are defined by red tests before production code. The intended families are:

```c
BreakWorldSnapshot *break_world_snapshot_build(const World *world,
                                               const BreakComponentSchemaRegistry *schemas,
                                               uint64_t tick);
void break_world_snapshot_retain(BreakWorldSnapshot *snapshot);
void break_world_snapshot_release(BreakWorldSnapshot *snapshot);

BreakWorldDelta *break_world_delta_diff(const BreakWorldSnapshot *base,
                                        const BreakWorldSnapshot *target);
BreakDeltaApplyResult break_world_delta_apply(World *world,
                                              const BreakWorldDelta *delta);

BreakAoIResult break_aoi_compute(const BreakWitness *witnesses,
                                 size_t witness_count,
                                 const BreakSpatialIndex *index,
                                 BreakConnectionKey connection);
```

These APIs must not expose internal ECS pointers. The first implementation may use stop-the-world snapshot build and a simple spatial grid; it must not prematurely add prediction, rollback, authority handoff, or distributed Cell services.

## Acceptance

Tests must prove deep-copy immutability, generation-aware identity, deterministic snapshot hashing, reader lifetime, delta create/destroy/add/remove/update classification, base mismatch rejection, delta idempotence, enter/stay/leave scope computation, spatial boundary behavior, and fragmentation/reassembly without mutating World before complete validation.
