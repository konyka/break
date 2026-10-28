#include "break_aoi.h"

#include <math.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    BreakReplicationObject object;
    i32 cell[3];
} BreakSpatialEntry;

typedef struct {
    i32 cell[3];
    BreakAoIEntityId *ids;
    usize count;
    usize capacity;
} BreakSpatialBucket;

struct BreakSpatialIndex {
    f32 cell_size;
    BreakSpatialEntry *entries;
    usize count;
    usize capacity;
    BreakSpatialBucket *buckets;
    usize bucket_count;
    usize bucket_capacity;
};

static bool size_add(usize a, usize b, usize *out) {
    if (b > (usize)-1 - a) return false;
    *out = a + b; return true;
}

static bool size_mul(usize a, usize b, usize *out) {
    if (a && b > (usize)-1 / a) return false;
    *out = a * b; return true;
}

static bool grow(void **data, usize *capacity, usize item_size, usize needed) {
    usize next, bytes;
    void *memory;
    if (needed <= *capacity) return true;
    next = *capacity ? *capacity : 16u;
    while (next < needed) {
        if (next > (usize)-1 / 2u) return false;
        next *= 2u;
    }
    if (!size_mul(next, item_size, &bytes)) return false;
    memory = realloc(*data, bytes);
    if (!memory) return false;
    *data = memory;
    *capacity = next;
    return true;
}

static bool cell_coord(f32 value, f32 cell_size, i32 *out) {
    f32 quotient;
    if (!isfinite(value) || !isfinite(cell_size)) return false;
    quotient = floorf(value / cell_size);
    if (!isfinite(quotient) || quotient < (f32)INT32_MIN || quotient > (f32)INT32_MAX) return false;
    *out = (i32)quotient;
    return true;
}

static bool set_cell(BreakSpatialEntry *entry, f32 cell_size) {
    return cell_coord(entry->object.position[0], cell_size, &entry->cell[0]) &&
           cell_coord(entry->object.position[1], cell_size, &entry->cell[1]) &&
           cell_coord(entry->object.position[2], cell_size, &entry->cell[2]);
}

BreakSpatialIndex *break_spatial_index_create(f32 cell_size) {
    BreakSpatialIndex *index;
    if (!(cell_size > 0.0f) || !isfinite(cell_size)) return NULL;
    index = (BreakSpatialIndex *)calloc(1u, sizeof(*index));
    if (!index) return NULL;
    index->cell_size = cell_size;
    return index;
}

static BreakSpatialBucket *find_bucket(BreakSpatialIndex *index, const i32 cell[3]) {
    for (usize i = 0u; i < index->bucket_count; i++) {
        if (index->buckets[i].cell[0] == cell[0] && index->buckets[i].cell[1] == cell[1] &&
            index->buckets[i].cell[2] == cell[2]) return &index->buckets[i];
    }
    return NULL;
}

static bool bucket_add(BreakSpatialIndex *index, const i32 cell[3], BreakAoIEntityId id) {
    BreakSpatialBucket *bucket = find_bucket(index, cell);
    bool new_bucket = false;
    usize next_count;
    if (!bucket) {
        if (!size_add(index->bucket_count, 1u, &next_count) ||
            !grow((void **)&index->buckets, &index->bucket_capacity,
                  sizeof(*index->buckets), next_count)) return false;
        bucket = &index->buckets[index->bucket_count];
        memset(bucket, 0, sizeof(*bucket));
        memcpy(bucket->cell, cell, sizeof(bucket->cell));
        new_bucket = true;
    }
    if (!size_add(bucket->count, 1u, &next_count) ||
        !grow((void **)&bucket->ids, &bucket->capacity, sizeof(*bucket->ids), next_count)) return false;
    bucket->ids[bucket->count++] = id;
    if (new_bucket) index->bucket_count++;
    return true;
}

static bool bucket_remove(BreakSpatialIndex *index, const i32 cell[3], BreakAoIEntityId id) {
    BreakSpatialBucket *bucket = find_bucket(index, cell);
    if (!bucket) return false;
    for (usize i = 0u; i < bucket->count; i++) if (bucket->ids[i] == id) {
        bucket->ids[i] = bucket->ids[--bucket->count];
        return true;
    }
    return false;
}

void break_spatial_index_destroy(BreakSpatialIndex *index) {
    if (!index) return;
    for (usize i = 0u; i < index->bucket_count; i++) free(index->buckets[i].ids);
    free(index->buckets);
    free(index->entries);
    free(index);
}

bool break_spatial_index_insert(BreakSpatialIndex *index,
                                const BreakReplicationObject *object) {
    i32 cell[3];
    usize next_count;
    if (!index || !object || !isfinite(object->position[0]) || !isfinite(object->position[1]) ||
        !isfinite(object->position[2]) || !set_cell(&(BreakSpatialEntry){.object = *object}, index->cell_size)) return false;
    for (usize i = 0u; i < index->count; i++) {
        if (index->entries[i].object.entity_id == object->entity_id) {
            BreakSpatialEntry replacement = index->entries[i];
            BreakSpatialBucket *old_bucket;
            if (!set_cell(&(BreakSpatialEntry){.object = *object, .cell = {0, 0, 0}}, index->cell_size)) return false;
            replacement.object = *object;
            if (!set_cell(&replacement, index->cell_size)) return false;
            memcpy(cell, replacement.cell, sizeof(cell));
            old_bucket = find_bucket(index, index->entries[i].cell);
            if (!old_bucket || !bucket_add(index, cell, object->entity_id)) return false;
            if (!bucket_remove(index, index->entries[i].cell, object->entity_id)) {
                if (!bucket_remove(index, cell, object->entity_id) ||
                    !bucket_add(index, index->entries[i].cell, object->entity_id)) return false;
                return false;
            }
            index->entries[i] = replacement;
            return true;
        }
    }
    if (!size_add(index->count, 1u, &next_count) || !grow((void **)&index->entries, &index->capacity,
              sizeof(*index->entries), next_count)) return false;
    index->entries[index->count].object = *object;
    if (!set_cell(&index->entries[index->count], index->cell_size)) return false;
    memcpy(cell, index->entries[index->count].cell, sizeof(cell));
    if (!bucket_add(index, cell, object->entity_id)) return false;
    index->count++;
    return true;
}

bool break_spatial_index_remove(BreakSpatialIndex *index,
                                BreakAoIEntityId entity_id) {
    if (!index) return false;
    for (usize i = 0u; i < index->count; i++) {
        if (index->entries[i].object.entity_id == entity_id) {
            if (!bucket_remove(index, index->entries[i].cell, entity_id)) return false;
            if (i < index->count - 1u) {
                BreakSpatialEntry removed = index->entries[i];
                BreakSpatialEntry moved = index->entries[index->count - 1u];
                if (!bucket_remove(index, moved.cell, moved.object.entity_id)) {
                    if (!bucket_add(index, removed.cell, removed.object.entity_id)) return false;
                    return false;
                }
                if (!bucket_add(index, moved.cell, moved.object.entity_id)) {
                    bool restored_moved = bucket_add(index, moved.cell, moved.object.entity_id);
                    bool restored_removed = bucket_add(index, removed.cell, removed.object.entity_id);
                    if (!restored_moved || !restored_removed) return false;
                    return false;
                }
                index->entries[i] = moved;
            }
            index->count--;
            return true;
        }
    }
    return false;
}

void break_spatial_index_clear(BreakSpatialIndex *index) {
    if (index) {
        for (usize i = 0u; i < index->bucket_count; i++) index->buckets[i].count = 0u;
        index->count = 0u;
    }
}

static bool id_contains(const BreakAoIEntityId *ids, usize count,
                        BreakAoIEntityId id) {
    usize i;
    for (i = 0u; i < count; i++) if (ids[i] == id) return true;
    return false;
}

typedef struct {
    BreakAoIEntityId id;
    u32 priority;
} BreakAoICandidate;

static int id_compare(const void *left, const void *right) {
    BreakAoIEntityId a = *(const BreakAoIEntityId *)left;
    BreakAoIEntityId b = *(const BreakAoIEntityId *)right;
    return a < b ? -1 : (a > b ? 1 : 0);
}

static int candidate_compare(const void *left, const void *right) {
    const BreakAoICandidate *a = (const BreakAoICandidate *)left;
    const BreakAoICandidate *b = (const BreakAoICandidate *)right;
    if (a->priority != b->priority) return a->priority > b->priority ? -1 : 1;
    return a->id < b->id ? -1 : (a->id > b->id ? 1 : 0);
}

static bool candidate_contains(const BreakAoICandidate *items, usize count,
                               BreakAoIEntityId id) {
    for (usize i = 0u; i < count; i++) if (items[i].id == id) return true;
    return false;
}

void break_aoi_result_clear(BreakAoIResult *result) {
    if (!result) return;
    free(result->enter);
    free(result->stay);
    free(result->leave);
    memset(result, 0, sizeof(*result));
}

void break_aoi_scope_clear(BreakAoIScope *scope) {
    if (!scope) return;
    free(scope->ids);
    memset(scope, 0, sizeof(*scope));
}

bool break_aoi_scope_assign(BreakAoIScope *scope,
                            const BreakAoIEntityId *ids, usize count) {
    BreakAoIEntityId *copy = NULL;
    if (!scope || (count && !ids)) return false;
    if (count) {
        usize bytes;
        if (!size_mul(count, sizeof(*copy), &bytes)) return false;
        copy = (BreakAoIEntityId *)malloc(bytes);
        if (!copy) return false;
        memcpy(copy, ids, bytes);
        qsort(copy, count, sizeof(*copy), id_compare);
    }
    if (count) {
        usize unique = 1u;
        for (usize i = 1u; i < count; i++) {
            if (copy[i] != copy[unique - 1u]) copy[unique++] = copy[i];
        }
        count = unique;
    }
    free(scope->ids);
    scope->ids = copy;
    scope->count = count;
    scope->capacity = count;
    return true;
}

static bool relevant(const BreakReplicationObject *object,
                     const BreakWitness *witness) {
    if (object->flags & BREAK_AOI_OBJECT_DORMANT) return false;
    return !(object->flags & BREAK_AOI_OBJECT_OWNER_ONLY) ||
           object->owner_id == witness->connection_id;
}

static bool valid_witness(const BreakWitness *witness) {
    if (!witness || !isfinite(witness->position[0]) || !isfinite(witness->position[1]) ||
        !isfinite(witness->position[2]) || !isfinite(witness->radius) || witness->radius < 0.0f ||
        !isfinite(witness->enter_hysteresis) || witness->enter_hysteresis < 0.0f ||
        !isfinite(witness->leave_hysteresis) || witness->leave_hysteresis < 0.0f ||
        (witness->shape != BREAK_AOI_SHAPE_SPHERE && witness->shape != BREAK_AOI_SHAPE_AABB)) return false;
    for (usize i = 0u; i < 3u; i++) if (!isfinite(witness->half_extents[i]) || witness->half_extents[i] < 0.0f) return false;
    return true;
}

static BreakSpatialEntry *find_entry(const BreakSpatialIndex *index, BreakAoIEntityId id) {
    for (usize i = 0u; i < index->count; i++) if (index->entries[i].object.entity_id == id) return &index->entries[i];
    return NULL;
}

static bool inside(const BreakReplicationObject *object, const BreakWitness *witness,
                   bool was_relevant) {
    f32 dx = object->position[0] - witness->position[0];
    f32 dy = object->position[1] - witness->position[1];
    f32 dz = object->position[2] - witness->position[2];
    f32 margin = was_relevant ? witness->leave_hysteresis : witness->enter_hysteresis;
    if (margin < 0.0f) margin = 0.0f;
    if (witness->shape == BREAK_AOI_SHAPE_AABB) {
        return fabsf(dx) <= witness->half_extents[0] + margin &&
               fabsf(dy) <= witness->half_extents[1] + margin &&
               fabsf(dz) <= witness->half_extents[2] + margin;
    }
    {
        f64 radius = (f64)witness->radius + (f64)margin;
        f64 distance_squared = (f64)dx * (f64)dx + (f64)dy * (f64)dy + (f64)dz * (f64)dz;
        f64 radius_squared = radius * radius;
        return isfinite(radius) && isfinite(distance_squared) && isfinite(radius_squared) &&
               radius >= 0.0 && distance_squared <= radius_squared;
    }
}

bool break_aoi_compute(const BreakSpatialIndex *index,
                       const BreakWitness *witnesses, usize witness_count,
                       const BreakAoIScope *previous, BreakAoIResult *result) {
    BreakAoICandidate *current = NULL;
    usize current_count = 0u, current_capacity = 0u, i, w;
    BreakAoIEntityId *ids = NULL;
    usize id_count = 0u, id_capacity = 0u;
    if (!index || !result || (witness_count && !witnesses)) return false;
    for (w = 0u; w < witness_count; w++) if (!valid_witness(&witnesses[w])) return false;
    break_aoi_result_clear(result);
    for (i = 0u; i < index->count; i++) {
        const BreakReplicationObject *object = &index->entries[i].object;
        if (object->flags & BREAK_AOI_OBJECT_ALWAYS_RELEVANT) {
            usize next_count;
            if (!size_add(id_count, 1u, &next_count) ||
                !grow((void **)&ids, &id_capacity, sizeof(*ids), next_count)) { free(ids); return false; }
            ids[id_count++] = object->entity_id;
        }
    }
    for (w = 0u; w < witness_count; w++) {
        f32 hysteresis = witnesses[w].enter_hysteresis > witnesses[w].leave_hysteresis
            ? witnesses[w].enter_hysteresis : witnesses[w].leave_hysteresis;
        f32 margin = witnesses[w].radius + hysteresis;
        f32 minv[3], maxv[3];
        if (witnesses[w].shape == BREAK_AOI_SHAPE_AABB) {
            for (i = 0u; i < 3u; i++) { minv[i] = witnesses[w].position[i] - witnesses[w].half_extents[i] - hysteresis; maxv[i] = witnesses[w].position[i] + witnesses[w].half_extents[i] + hysteresis; }
        } else {
            for (i = 0u; i < 3u; i++) { minv[i] = witnesses[w].position[i] - margin; maxv[i] = witnesses[w].position[i] + margin; }
        }
        i32 minc[3], maxc[3];
        for (i = 0u; i < 3u; i++) if (!cell_coord(minv[i], index->cell_size, &minc[i]) || !cell_coord(maxv[i], index->cell_size, &maxc[i])) { free(ids); return false; }
        for (usize b = 0u; b < index->bucket_count; b++) {
            BreakSpatialBucket *bucket = &index->buckets[b];
            if (bucket->cell[0] < minc[0] || bucket->cell[0] > maxc[0] || bucket->cell[1] < minc[1] || bucket->cell[1] > maxc[1] || bucket->cell[2] < minc[2] || bucket->cell[2] > maxc[2]) continue;
            for (usize k = 0u; k < bucket->count; k++) if (!id_contains(ids, id_count, bucket->ids[k])) {
                usize next_count;
                if (!size_add(id_count, 1u, &next_count) ||
                    !grow((void **)&ids, &id_capacity, sizeof(*ids), next_count)) { free(ids); return false; }
                ids[id_count++] = bucket->ids[k];
            }
        }
    }
    for (i = 0u; i < id_count; i++) {
        BreakSpatialEntry *entry = find_entry(index, ids[i]);
        const BreakReplicationObject *object = entry ? &entry->object : NULL;
        if (!object) continue;
        bool was = previous && id_contains(previous->ids, previous->count, object->entity_id);
        bool include = false;
        if (!(object->flags & BREAK_AOI_OBJECT_DORMANT)) {
            if (witness_count == 0u) {
                include = (object->flags & BREAK_AOI_OBJECT_ALWAYS_RELEVANT) &&
                          !(object->flags & BREAK_AOI_OBJECT_OWNER_ONLY);
            } else {
                for (w = 0u; w < witness_count && !include; w++) {
                    if (!relevant(object, &witnesses[w])) continue;
                    if ((object->flags & BREAK_AOI_OBJECT_ALWAYS_RELEVANT) ||
                        inside(object, &witnesses[w], was)) include = true;
                }
            }
        }
        if (include) {
            usize next_count;
            if (!size_add(current_count, 1u, &next_count) ||
                !grow((void **)&current, &current_capacity, sizeof(*current), next_count)) {
                free(current); return false;
            }
            current[current_count++] = (BreakAoICandidate){object->entity_id, object->priority};
        }
    }
    free(ids);
    if (current_count > 1u) qsort(current, current_count, sizeof(*current), candidate_compare);
    for (i = 0u; i < current_count; i++) {
        usize next_count, bytes;
        bool was = previous && id_contains(previous->ids, previous->count, current[i].id);
        BreakAoIEntityId **target = was ? &result->stay : &result->enter;
        usize *count = was ? &result->stay_count : &result->enter_count;
        BreakAoIEntityId *memory;
        if (!size_add(*count, 1u, &next_count) || !size_mul(next_count, sizeof(**target), &bytes)) { free(current); break_aoi_result_clear(result); return false; }
        memory = (BreakAoIEntityId *)realloc(*target, bytes);
        if (!memory) { free(current); break_aoi_result_clear(result); return false; }
        *target = memory;
        (*target)[(*count)++] = current[i].id;
    }
    if (previous) {
        BreakAoICandidate *leaving = NULL;
        usize leaving_count = 0u, leaving_capacity = 0u;
        for (i = 0u; i < previous->count; i++) {
            if (!candidate_contains(current, current_count, previous->ids[i])) {
                BreakSpatialEntry *entry = find_entry(index, previous->ids[i]);
                usize next_count;
                if (!size_add(leaving_count, 1u, &next_count) ||
                    !grow((void **)&leaving, &leaving_capacity, sizeof(*leaving), next_count)) {
                    free(leaving); free(current); break_aoi_result_clear(result); return false;
                }
                leaving[leaving_count++] = (BreakAoICandidate){
                    previous->ids[i], entry ? entry->object.priority : 0u};
            }
        }
        if (leaving_count > 1u) qsort(leaving, leaving_count, sizeof(*leaving), candidate_compare);
        for (i = 0u; i < leaving_count; i++) {
            usize next_count, bytes;
            BreakAoIEntityId *memory;
            if (!size_add(result->leave_count, 1u, &next_count) ||
                !size_mul(next_count, sizeof(*memory), &bytes)) {
                free(leaving); free(current); break_aoi_result_clear(result); return false;
            }
            memory = (BreakAoIEntityId *)realloc(result->leave, bytes);
            if (!memory) {
                free(leaving); free(current); break_aoi_result_clear(result); return false;
            }
            result->leave = memory;
            result->leave[result->leave_count++] = leaving[i].id;
        }
        free(leaving);
    }
    free(current);
    return true;
}
