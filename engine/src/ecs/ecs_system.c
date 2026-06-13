#include <ecs/ecs_system.h>
#include <core/log.h>
#include <stdlib.h>
#include <string.h>

void *ecs_chunk_column(const EcsChunkView *view, ComponentType comp) {
    if (!view || !view->archetype || !view->chunk) return NULL;
    Archetype *a = view->archetype;
    for (u32 i = 0; i < a->key.count; i++) {
        if (a->key.ids[i] == comp) {
            return (u8 *)view->chunk + a->offsets[i];
        }
    }
    return NULL;
}

const u32 *ecs_chunk_entity_ids(const EcsChunkView *view) {
    if (!view || !view->archetype || !view->chunk) return NULL;
    return (const u32 *)((u8 *)view->chunk + view->archetype->entity_offset);
}

/* ---- Parallel-for over matching chunks ---- */

typedef struct {
    EcsChunkView view;
    EcsSystemFn  fn;
    void        *user;
} EcsJob;

static void ecs_job_run(void *ctx) {
    EcsJob *j = (EcsJob *)ctx;
    j->fn(&j->view, j->user);
}

/* Persistent job pool avoids per-frame heap alloc/free for typical workloads */
#define ECS_JOB_POOL_SIZE 512
static EcsJob _job_pool[ECS_JOB_POOL_SIZE];

void ecs_parallel_for(World *w, TaskSystem *ts,
                      const ComponentType *types, u32 count,
                      EcsSystemFn fn, void *user) {
    if (!w || !fn || !types || count == 0) return;

    Query *q = world_query(w, types, count);
    if (!q || q->match_count == 0) {
        if (q) query_done(q);
        return;
    }

    /* Count non-empty chunks to size the job array. */
    u32 job_count = 0;
    for (u32 ai = 0; ai < q->match_count; ai++) {
        for (Chunk *c = q->matching[ai]->chunks; c; c = c->next) {
            if (c->count > 0) job_count++;
        }
    }
    if (job_count == 0) { query_done(q); return; }

    EcsJob *jobs;
    bool heap_fallback = false;
    if (job_count <= ECS_JOB_POOL_SIZE) {
        jobs = _job_pool;
    } else {
        jobs = (EcsJob *)malloc(job_count * sizeof(EcsJob));
        heap_fallback = true;
    }
    u32 ji = 0;
    for (u32 ai = 0; ai < q->match_count; ai++) {
        Archetype *a = q->matching[ai];
        for (Chunk *c = a->chunks; c; c = c->next) {
            if (c->count == 0) continue;
            jobs[ji].view.world     = w;
            jobs[ji].view.archetype = a;
            jobs[ji].view.chunk     = c;
            jobs[ji].view.count     = c->count;
            jobs[ji].fn             = fn;
            jobs[ji].user           = user;
            ji++;
        }
    }

    if (ts && job_count > 1) {
        for (u32 i = 0; i < job_count; i++) {
            task_submit(ts, ecs_job_run, &jobs[i]);
        }
        task_wait(ts);
    } else {
        for (u32 i = 0; i < job_count; i++) {
            ecs_job_run(&jobs[i]);
        }
    }

    if (heap_fallback) free(jobs);
    query_done(q);
}

/* ---- System scheduler ---- */

void ecs_scheduler_init(EcsScheduler *s) {
    if (!s) return;
    memset(s, 0, sizeof(*s));
}

bool ecs_system_register(EcsScheduler *s, const char *name,
                         const ComponentType *types, u32 type_count,
                         EcsSystemFn fn, void *user, bool parallel) {
    if (!s || !fn || !types || type_count == 0) return false;
    if (type_count > ECS_SYSTEM_MAX_COMPONENTS) return false;
    if (s->count >= ECS_MAX_SYSTEMS) {
        LOG_WARN("ECS scheduler: system limit (%d) reached", ECS_MAX_SYSTEMS);
        return false;
    }
    EcsSystem *sys = &s->systems[s->count++];
    memset(sys, 0, sizeof(*sys));
    if (name) {
        size_t n = strlen(name);
        if (n >= sizeof(sys->name)) n = sizeof(sys->name) - 1;
        memcpy(sys->name, name, n);
        sys->name[n] = '\0';
    }
    memcpy(sys->types, types, type_count * sizeof(ComponentType));
    sys->type_count = type_count;
    sys->fn         = fn;
    sys->user       = user;
    sys->parallel   = parallel;
    return true;
}

void ecs_scheduler_run(EcsScheduler *s, World *w, TaskSystem *ts) {
    if (!s || !w) return;
    for (u32 i = 0; i < s->count; i++) {
        EcsSystem *sys = &s->systems[i];
        TaskSystem *use_ts = sys->parallel ? ts : NULL;
        ecs_parallel_for(w, use_ts, sys->types, sys->type_count, sys->fn, sys->user);
    }
}

u32 ecs_scheduler_system_count(const EcsScheduler *s) {
    return s ? s->count : 0;
}
