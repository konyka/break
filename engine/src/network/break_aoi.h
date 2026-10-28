#ifndef BREAK_AOI_H
#define BREAK_AOI_H

#include "../core/types.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef u64 BreakAoIEntityId;

typedef enum {
    BREAK_AOI_SHAPE_SPHERE = 0,
    BREAK_AOI_SHAPE_AABB = 1
} BreakAoIShape;

enum {
    BREAK_AOI_OBJECT_ALWAYS_RELEVANT = 1u << 0,
    BREAK_AOI_OBJECT_OWNER_ONLY = 1u << 1,
    BREAK_AOI_OBJECT_DORMANT = 1u << 2
};

typedef struct {
    f32 position[3];
    f32 direction[3];
    f32 velocity[3];
    f32 radius;
    u32 flags;
    u32 priority;
    u64 connection_id;
    f32 half_extents[3];
    f32 enter_hysteresis;
    f32 leave_hysteresis;
    BreakAoIShape shape;
} BreakWitness;

typedef struct {
    BreakAoIEntityId entity_id;
    u64 owner_id;
    f32 position[3];
    u32 flags;
    u32 priority;
} BreakReplicationObject;

typedef struct BreakSpatialIndex BreakSpatialIndex;

typedef struct {
    BreakAoIEntityId *ids;
    usize count;
    usize capacity;
} BreakAoIScope;

typedef struct {
    BreakAoIEntityId *enter;
    usize enter_count;
    BreakAoIEntityId *stay;
    usize stay_count;
    BreakAoIEntityId *leave;
    usize leave_count;
} BreakAoIResult;

BreakSpatialIndex *break_spatial_index_create(f32 cell_size);
void break_spatial_index_destroy(BreakSpatialIndex *index);
bool break_spatial_index_insert(BreakSpatialIndex *index,
                                const BreakReplicationObject *object);
bool break_spatial_index_remove(BreakSpatialIndex *index,
                                BreakAoIEntityId entity_id);
void break_spatial_index_clear(BreakSpatialIndex *index);

bool break_aoi_compute(const BreakSpatialIndex *index,
                       const BreakWitness *witnesses, usize witness_count,
                       const BreakAoIScope *previous, BreakAoIResult *result);
void break_aoi_result_clear(BreakAoIResult *result);
bool break_aoi_scope_assign(BreakAoIScope *scope,
                            const BreakAoIEntityId *ids, usize count);
void break_aoi_scope_clear(BreakAoIScope *scope);

#ifdef __cplusplus
}
#endif

#endif
