#include <physics/physics_task.h>
#include <stdatomic.h>

typedef struct {
    PhysicsJobFn fn;
    void *job_ctx;
    u32 index;
    atomic_uint *remaining;
} PhysicsTaskJob;

static void physics_task_run(void *raw) {
    PhysicsTaskJob *job = (PhysicsTaskJob *)raw;
    job->fn(job->job_ctx, job->index);
    atomic_fetch_sub_explicit(job->remaining, 1u, memory_order_release);
}

/* Waits on a per-call counter rather than task handles: the task pool hands
 * out heap-fallback handles once 4096 tasks have been submitted over the
 * process lifetime, and waiting on one of those waits for every task in the
 * system. */
void physics_task_parallel_for(void *user, PhysicsJobFn fn, void *job_ctx, u32 job_count) {
    TaskSystem *ts = (TaskSystem *)user;
    if (!fn || job_count == 0u) return;
    u32 queued = job_count < PHYSICS_MAX_PARALLEL_JOBS ? job_count : PHYSICS_MAX_PARALLEL_JOBS;
    if (!ts || task_worker_id(ts) >= 0) queued = 1u;
    PhysicsTaskJob jobs[PHYSICS_MAX_PARALLEL_JOBS];
    atomic_uint remaining;
    atomic_init(&remaining, 0u);
    for (u32 i = 1; i < queued; i++) {
        jobs[i].fn = fn;
        jobs[i].job_ctx = job_ctx;
        jobs[i].index = i;
        jobs[i].remaining = &remaining;
        atomic_fetch_add_explicit(&remaining, 1u, memory_order_relaxed);
        if (task_submit_ex(ts, physics_task_run, &jobs[i], TASK_PRIORITY_HIGH) == TASK_HANDLE_INVALID) {
            atomic_fetch_sub_explicit(&remaining, 1u, memory_order_relaxed);
            fn(job_ctx, i);
        }
    }
    fn(job_ctx, 0u);
    for (u32 i = queued; i < job_count; i++) fn(job_ctx, i);
    while (atomic_load_explicit(&remaining, memory_order_acquire) != 0u) platform_thread_yield();
}
