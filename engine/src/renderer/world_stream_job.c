#include <renderer/world_stream_job.h>

typedef struct StreamApplyJob {
    const StreamWant *wants;
    u32 count;
    bool *resident;
    u32 tile_count_x;
    u32 tile_count_z;
    u32 applied;
    u32 rejected;
} StreamApplyJob;

static void stream_apply_run(void *ctx) {
    StreamApplyJob *job = (StreamApplyJob *)ctx;
    for (u32 i = 0; i < job->count; i++) {
        u32 x = job->wants[i].tile_x;
        u32 z = job->wants[i].tile_z;
        if (x >= job->tile_count_x || z >= job->tile_count_z) {
            job->rejected++;
            continue;
        }
        job->resident[z * job->tile_count_x + x] = job->wants[i].resident;
        job->applied++;
    }
}

u32 world_stream_apply(TaskSystem *tasks, const StreamWant *wants, u32 count,
                       bool *resident, u32 tile_count_x, u32 tile_count_z,
                       u32 *rejected) {
    if (rejected) *rejected = 0;
    if (!tasks || !wants || !resident || count == 0 || tile_count_x == 0 || tile_count_z == 0) {
        return 0;
    }
    StreamApplyJob job;
    job.wants = wants;
    job.count = count;
    job.resident = resident;
    job.tile_count_x = tile_count_x;
    job.tile_count_z = tile_count_z;
    job.applied = 0;
    job.rejected = 0;
    task_submit(tasks, stream_apply_run, &job);
    task_wait(tasks);
    if (rejected) *rejected = job.rejected;
    return job.applied;
}
