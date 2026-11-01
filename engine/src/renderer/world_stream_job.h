#pragma once
#include <renderer/world_stream.h>
#include <task/task.h>

/* Submit one task that writes `resident` from `wants`, then wait until it
 * finishes. Out-of-range tiles increment *rejected and leave those cells
 * unchanged. Returns the number of tiles written. */
u32 world_stream_apply(TaskSystem *tasks, const StreamWant *wants, u32 count,
                       bool *resident, u32 tile_count_x, u32 tile_count_z,
                       u32 *rejected);
