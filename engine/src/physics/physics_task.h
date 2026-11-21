#pragma once
#include <physics/physics.h>
#include <task/task.h>

/* PhysicsParallelForFn backed by the engine TaskSystem: user is the
 * TaskSystem. Job 0 runs on the calling thread and jobs 1 to
 * PHYSICS_MAX_PARALLEL_JOBS - 1 are submitted as tasks; the call returns
 * once all of them have finished (release/acquire, so their writes are
 * visible). Jobs beyond the cap, jobs whose task cannot be submitted, and
 * every job when called from a worker thread (where waiting could
 * deadlock) run inline on the calling thread. */
void physics_task_parallel_for(void *user, PhysicsJobFn fn, void *job_ctx, u32 job_count);
