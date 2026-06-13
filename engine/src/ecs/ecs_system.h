#pragma once
#include <ecs/ecs.h>
#include <task/task.h>

/* ==========================================================================
 *  ECS System Scheduler — task-parallel system execution over archetypes.
 *
 *  A "system" is a function run once per matching (non-empty) archetype chunk.
 *  Chunks of a single system can be dispatched across the task system's worker
 *  threads; systems themselves run in registration order so that two systems
 *  writing overlapping component columns never race.
 * ========================================================================== */

#define ECS_SYSTEM_MAX_COMPONENTS 8
#define ECS_MAX_SYSTEMS           64

/* Per-chunk view handed to a system callback. */
typedef struct {
    World     *world;
    Archetype *archetype;
    Chunk     *chunk;
    u32        count;   /* entities present in this chunk */
} EcsChunkView;

/* SoA column base pointer for `comp` inside this chunk (NULL if absent).
 * Element i of the column is `((T*)base)[i]`. */
void       *ecs_chunk_column(const EcsChunkView *view, ComponentType comp);
/* Entity index column (u32) for this chunk. */
const u32  *ecs_chunk_entity_ids(const EcsChunkView *view);

typedef void (*EcsSystemFn)(EcsChunkView *view, void *user);

/* Run `fn` once per matching non-empty chunk.
 * - ts != NULL: chunks dispatched to workers; blocks until all complete.
 * - ts == NULL: runs serially on the calling thread. */
void ecs_parallel_for(World *w, TaskSystem *ts,
                      const ComponentType *types, u32 count,
                      EcsSystemFn fn, void *user);

typedef struct {
    char          name[48];
    ComponentType types[ECS_SYSTEM_MAX_COMPONENTS];
    u32           type_count;
    EcsSystemFn   fn;
    void         *user;
    bool          parallel; /* dispatch this system's chunks across workers */
} EcsSystem;

typedef struct {
    EcsSystem systems[ECS_MAX_SYSTEMS];
    u32       count;
} EcsScheduler;

void ecs_scheduler_init(EcsScheduler *s);

/* Register a system. Returns false if full / invalid. `types` is the component
 * signature the system queries; `parallel` controls worker dispatch. */
bool ecs_system_register(EcsScheduler *s, const char *name,
                         const ComponentType *types, u32 type_count,
                         EcsSystemFn fn, void *user, bool parallel);

/* Execute all registered systems in registration order. */
void ecs_scheduler_run(EcsScheduler *s, World *w, TaskSystem *ts);

u32  ecs_scheduler_system_count(const EcsScheduler *s);
