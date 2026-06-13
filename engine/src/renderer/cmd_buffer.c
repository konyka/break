/*
 * cmd_buffer.c — multi-threaded render command recording and replay.
 *
 * Design:
 *   - Each worker writes into its own RenderCmdBuffer (no shared writes ->
 *     no locks required during recording).
 *   - Double-buffered submission: main thread swaps buffers at end of frame
 *     and signals the submit thread to replay the previous frame's commands
 *     while workers record into the next frame's buffers.
 *
 *   The recording API performs simple overflow checks and silently drops
 *   commands when a thread-local buffer is full. This keeps the hot path
 *   branch-light and avoids dynamic allocation.
 */

#include "cmd_buffer.h"

#include <core/log.h>

#include <string.h>
#include <stdlib.h>

/* ============================================================ */
/*                       Lifecycle                              */
/* ============================================================ */

void parallel_renderer_init(ParallelRenderer *pr, u32 thread_count) {
    if (!pr) {
        return;
    }
    if (thread_count == 0) {
        thread_count = 1;
    }
    if (thread_count > CMD_BUFFER_MAX_THREADS) {
        thread_count = CMD_BUFFER_MAX_THREADS;
    }

    memset(pr, 0, sizeof(*pr));
    pr->thread_count = thread_count;
    pr->write_frame = 0;
    pr->read_frame = 1;
    atomic_store(&pr->active_recorders, 0u);
    atomic_store(&pr->submit_pending, false);
    atomic_store(&pr->shutdown_requested, false);
    pr->recording = false;
    pr->submit_thread_running = false;
    
    /* Initialize synchronization primitives */
    pthread_mutex_init(&pr->submit_mutex, NULL);
    pthread_cond_init(&pr->submit_ready, NULL);
    pthread_cond_init(&pr->submit_done, NULL);
    
    /* Initialize frame buffers */
    for (int f = 0; f < 2; f++) {
        pr->frames[f].buffer_count = thread_count;
    }
}

void parallel_renderer_shutdown(ParallelRenderer *pr) {
    if (!pr) {
        return;
    }
    /* Stop submit thread if running */
    if (pr->submit_thread_running) {
        parallel_renderer_stop_submit_thread(pr);
    }
    /* Destroy synchronization primitives */
    pthread_mutex_destroy(&pr->submit_mutex);
    pthread_cond_destroy(&pr->submit_ready);
    pthread_cond_destroy(&pr->submit_done);
    /* Zero out so callers see a clean slate. */
    memset(pr, 0, sizeof(*pr));
}

/* ============================================================ */
/*                    Submit Thread                             */
/* ============================================================ */

static void *submit_thread_func(void *arg) {
    ParallelRenderer *pr = (ParallelRenderer *)arg;
    
    pthread_mutex_lock(&pr->submit_mutex);
    while (!atomic_load(&pr->shutdown_requested)) {
        /* Wait for submission signal */
        while (!atomic_load(&pr->submit_pending) && !atomic_load(&pr->shutdown_requested)) {
            pthread_cond_wait(&pr->submit_ready, &pr->submit_mutex);
        }
        
        if (atomic_load(&pr->shutdown_requested)) {
            break;
        }
        
        /* Perform submission on read frame */
        if (pr->rhi_cmd) {
            parallel_renderer_submit(pr, pr->rhi_cmd);
        }
        
        atomic_store(&pr->submit_pending, false);
        pthread_cond_signal(&pr->submit_done);
    }
    pthread_mutex_unlock(&pr->submit_mutex);
    
    return NULL;
}

bool parallel_renderer_start_submit_thread(ParallelRenderer *pr) {
    if (!pr || pr->submit_thread_running) {
        return false;
    }
    
    atomic_store(&pr->shutdown_requested, false);
    if (pthread_create(&pr->submit_thread, NULL, submit_thread_func, pr) != 0) {
        LOG_ERROR("Failed to create submit thread");
        return false;
    }
    pr->submit_thread_running = true;
    LOG_INFO("Render command submit thread started");
    return true;
}

void parallel_renderer_stop_submit_thread(ParallelRenderer *pr) {
    if (!pr || !pr->submit_thread_running) {
        return;
    }
    
    /* Wait for any pending submission to complete */
    parallel_renderer_wait_submit(pr);
    
    /* Signal shutdown */
    atomic_store(&pr->shutdown_requested, true);
    pthread_mutex_lock(&pr->submit_mutex);
    pthread_cond_signal(&pr->submit_ready);
    pthread_mutex_unlock(&pr->submit_mutex);
    
    pthread_join(pr->submit_thread, NULL);
    pr->submit_thread_running = false;
    LOG_INFO("Render command submit thread stopped");
}

/* ============================================================ */
/*                      Per-frame flow                          */
/* ============================================================ */

void parallel_renderer_begin_frame(ParallelRenderer *pr) {
    if (!pr) {
        return;
    }
    /* Reset buffers in the write frame */
    FrameCommands *frame = &pr->frames[pr->write_frame];
    for (u32 i = 0; i < pr->thread_count; ++i) {
        frame->buffers[i].count    = 0;
        frame->buffers[i].sort_key = 0;
    }
    atomic_store(&pr->active_recorders, 0u);
    pr->recording = true;
}

void parallel_renderer_end_frame(ParallelRenderer *pr) {
    if (!pr) {
        return;
    }
    pr->recording = false;
}

RenderCmdBuffer *parallel_renderer_get_buffer(ParallelRenderer *pr, u32 thread_id) {
    if (!pr || thread_id >= pr->thread_count) {
        return NULL;
    }
    /* Track concurrent recorders for diagnostics; lock-free. */
    atomic_fetch_add(&pr->active_recorders, 1u);
    /* Return buffer from the write frame */
    return &pr->frames[pr->write_frame].buffers[thread_id];
}

void parallel_renderer_set_rhi_cmd(ParallelRenderer *pr, RHICmdBuffer *rhi_cmd) {
    if (pr) {
        pr->rhi_cmd = rhi_cmd;
    }
}

/* ============================================================ */
/*                     Recording helpers                        */
/* ============================================================ */

/*
 * Reserve a slot in the command array. Returns NULL on overflow.
 * Recording is single-writer per buffer (per-thread), so no atomics here.
 */
static inline RenderCmd *cmd_buffer_reserve(RenderCmdBuffer *buf) {
    if (!buf) {
        return NULL;
    }
    if (buf->count >= CMD_BUFFER_MAX_COMMANDS) {
        return NULL;
    }
    return &buf->commands[buf->count++];
}

void cmd_draw(RenderCmdBuffer *buf, u32 vertex_count, u32 instance_count, u32 first_vertex) {
    RenderCmd *cmd = cmd_buffer_reserve(buf);
    if (!cmd) {
        return;
    }
    cmd->type                  = RENDER_CMD_DRAW;
    cmd->draw.vertex_count     = vertex_count;
    cmd->draw.instance_count   = instance_count;
    cmd->draw.first_vertex     = first_vertex;
}

void cmd_draw_indexed(RenderCmdBuffer *buf, u32 index_count, u32 instance_count,
                      u32 first_index, i32 vertex_offset) {
    RenderCmd *cmd = cmd_buffer_reserve(buf);
    if (!cmd) {
        return;
    }
    cmd->type                          = RENDER_CMD_DRAW_INDEXED;
    cmd->draw_indexed.index_count      = index_count;
    cmd->draw_indexed.instance_count   = instance_count;
    cmd->draw_indexed.first_index      = first_index;
    cmd->draw_indexed.vertex_offset    = vertex_offset;
}

void cmd_bind_pipeline(RenderCmdBuffer *buf, RHIPipeline pipeline) {
    RenderCmd *cmd = cmd_buffer_reserve(buf);
    if (!cmd) {
        return;
    }
    cmd->type                  = RENDER_CMD_BIND_PIPELINE;
    cmd->bind_pipeline.pipeline = pipeline;
}

void cmd_bind_vertex_buffer(RenderCmdBuffer *buf, RHIBuffer buffer, u32 offset) {
    RenderCmd *cmd = cmd_buffer_reserve(buf);
    if (!cmd) {
        return;
    }
    cmd->type            = RENDER_CMD_BIND_VERTEX_BUFFER;
    cmd->bind_vb.buffer  = buffer;
    cmd->bind_vb.offset  = offset;
}

void cmd_bind_index_buffer(RenderCmdBuffer *buf, RHIBuffer buffer, u32 offset, bool is_u32) {
    RenderCmd *cmd = cmd_buffer_reserve(buf);
    if (!cmd) {
        return;
    }
    cmd->type           = RENDER_CMD_BIND_INDEX_BUFFER;
    cmd->bind_ib.buffer = buffer;
    cmd->bind_ib.offset = offset;
    cmd->bind_ib.is_u32 = is_u32;
}

void cmd_bind_uniform(RenderCmdBuffer *buf, u32 binding, RHIBuffer buffer, u32 offset, u32 size) {
    RenderCmd *cmd = cmd_buffer_reserve(buf);
    if (!cmd) {
        return;
    }
    cmd->type                  = RENDER_CMD_BIND_UNIFORM;
    cmd->bind_uniform.binding  = binding;
    cmd->bind_uniform.buffer   = buffer;
    cmd->bind_uniform.offset   = offset;
    cmd->bind_uniform.size     = size;
}

void cmd_bind_texture(RenderCmdBuffer *buf, u32 slot, RHITexture texture) {
    RenderCmd *cmd = cmd_buffer_reserve(buf);
    if (!cmd) {
        return;
    }
    cmd->type                  = RENDER_CMD_BIND_TEXTURE;
    cmd->bind_texture.slot     = slot;
    cmd->bind_texture.texture  = texture;
}

void cmd_set_scissor(RenderCmdBuffer *buf, i32 x, i32 y, u32 w, u32 h) {
    RenderCmd *cmd = cmd_buffer_reserve(buf);
    if (!cmd) {
        return;
    }
    cmd->type        = RENDER_CMD_SET_SCISSOR;
    cmd->scissor.x   = x;
    cmd->scissor.y   = y;
    cmd->scissor.w   = w;
    cmd->scissor.h   = h;
}

void cmd_set_viewport(RenderCmdBuffer *buf, f32 x, f32 y, f32 w, f32 h, f32 min_d, f32 max_d) {
    RenderCmd *cmd = cmd_buffer_reserve(buf);
    if (!cmd) {
        return;
    }
    cmd->type                = RENDER_CMD_SET_VIEWPORT;
    cmd->viewport.x          = x;
    cmd->viewport.y          = y;
    cmd->viewport.w          = w;
    cmd->viewport.h          = h;
    cmd->viewport.min_depth  = min_d;
    cmd->viewport.max_depth  = max_d;
}

void cmd_push_constants(RenderCmdBuffer *buf, u32 offset, u32 size, const void *data) {
    if (size > CMD_BUFFER_PUSH_CONST_MAX) {
        size = CMD_BUFFER_PUSH_CONST_MAX;
    }
    RenderCmd *cmd = cmd_buffer_reserve(buf);
    if (!cmd) {
        return;
    }
    cmd->type                    = RENDER_CMD_PUSH_CONSTANTS;
    cmd->push_constants.offset   = offset;
    cmd->push_constants.size     = size;
    if (data && size > 0) {
        memcpy(cmd->push_constants.data, data, size);
    }
}

/* ============================================================ */
/*                          Submit                              */
/* ============================================================ */

/*
 * Stable insertion sort by sort_key. With at most CMD_BUFFER_MAX_THREADS=16
 * entries this is effectively constant-time and avoids pulling in qsort.
 */
static void sort_buffer_indices_by_key(const FrameCommands *frame,
                                       u32 *indices, u32 n) {
    for (u32 i = 1; i < n; ++i) {
        u32 cur     = indices[i];
        u32 cur_key = frame->buffers[cur].sort_key;
        i32 j       = (i32)i - 1;
        while (j >= 0 && frame->buffers[indices[j]].sort_key > cur_key) {
            indices[j + 1] = indices[j];
            --j;
        }
        indices[j + 1] = cur;
    }
}

/*
 * Replay a single command onto the RHI command buffer.
 *
 * NOTE: Some logical operations in the high-level command stream do not have
 * 1:1 RHI primitives yet (e.g. push_constants, draw_indexed first_index /
 * vertex_offset, viewport min/max depth). For those we map to the closest
 * available RHI call so the system compiles and behaves sanely; finer-grained
 * support is to be added as the RHI grows.
 */
static void replay_command(RHICmdBuffer *rhi_cmd, const RenderCmd *cmd) {
    switch (cmd->type) {
    case RENDER_CMD_DRAW:
        rhi_cmd_draw(rhi_cmd,
                     cmd->draw.vertex_count,
                     cmd->draw.instance_count);
        break;

    case RENDER_CMD_DRAW_INDEXED:
        /* RHI exposes (index_count, instance_count); first_index and
         * vertex_offset are recorded for future expansion. */
        rhi_cmd_draw_indexed(rhi_cmd,
                             cmd->draw_indexed.index_count,
                             cmd->draw_indexed.instance_count);
        break;

    case RENDER_CMD_BIND_PIPELINE:
        rhi_cmd_bind_pipeline(rhi_cmd, cmd->bind_pipeline.pipeline);
        break;

    case RENDER_CMD_BIND_VERTEX_BUFFER:
        rhi_cmd_bind_vertex_buffer(rhi_cmd,
                                   cmd->bind_vb.buffer,
                                   (usize)cmd->bind_vb.offset);
        break;

    case RENDER_CMD_BIND_INDEX_BUFFER:
        /* is_u32 will be honored once the RHI gains an index-type parameter. */
        rhi_cmd_bind_index_buffer(rhi_cmd,
                                  cmd->bind_ib.buffer,
                                  (usize)cmd->bind_ib.offset);
        break;

    case RENDER_CMD_BIND_UNIFORM:
        /* offset/size recorded for future dynamic-offset support. */
        rhi_cmd_bind_uniform_buffer(rhi_cmd,
                                    cmd->bind_uniform.buffer,
                                    cmd->bind_uniform.binding);
        break;

    case RENDER_CMD_BIND_TEXTURE: {
        /* Use a NULL/default sampler placeholder; concrete sampler binding is
         * the caller's responsibility through dedicated material APIs. */
        RHISampler default_sampler = RHI_HANDLE_NULL;
        rhi_cmd_bind_texture(rhi_cmd,
                             cmd->bind_texture.texture,
                             default_sampler,
                             cmd->bind_texture.slot);
        break;
    }

    case RENDER_CMD_SET_SCISSOR:
        rhi_cmd_set_scissor(rhi_cmd,
                            cmd->scissor.x,
                            cmd->scissor.y,
                            cmd->scissor.w,
                            cmd->scissor.h);
        break;

    case RENDER_CMD_SET_VIEWPORT:
        rhi_cmd_set_viewport(rhi_cmd,
                             cmd->viewport.x,
                             cmd->viewport.y,
                             cmd->viewport.w,
                             cmd->viewport.h);
        break;

    case RENDER_CMD_PUSH_CONSTANTS:
        /* No direct RHI counterpart yet — recorded but skipped on replay. */
        (void)cmd;
        break;

    default:
        LOG_WARN("cmd_buffer: unknown command type %d", (int)cmd->type);
        break;
    }
}

void parallel_renderer_submit(ParallelRenderer *pr, RHICmdBuffer *rhi_cmd) {
    if (!pr || !rhi_cmd) {
        return;
    }

    /* Use the read frame for submission */
    const FrameCommands *frame = &pr->frames[pr->read_frame];

    /* Build an index list of non-empty buffers, then sort by sort_key. */
    u32 indices[CMD_BUFFER_MAX_THREADS];
    u32 n = 0;
    for (u32 i = 0; i < pr->thread_count; ++i) {
        if (frame->buffers[i].count > 0) {
            indices[n++] = i;
        }
    }
    sort_buffer_indices_by_key(frame, indices, n);

    /* Replay each buffer in sorted order. */
    for (u32 k = 0; k < n; ++k) {
        const RenderCmdBuffer *buf = &frame->buffers[indices[k]];
        for (u32 i = 0; i < buf->count; ++i) {
            replay_command(rhi_cmd, &buf->commands[i]);
        }
    }
}

void parallel_renderer_swap_and_submit(ParallelRenderer *pr) {
    if (!pr) {
        return;
    }
    
    /* Wait for any previous submission to complete */
    parallel_renderer_wait_submit(pr);
    
    /* Swap frames: write frame becomes read frame */
    u32 temp = pr->write_frame;
    pr->write_frame = pr->read_frame;
    pr->read_frame = temp;
    
    /* Signal submit thread if running */
    if (pr->submit_thread_running) {
        atomic_store(&pr->submit_pending, true);
        pthread_mutex_lock(&pr->submit_mutex);
        pthread_cond_signal(&pr->submit_ready);
        pthread_mutex_unlock(&pr->submit_mutex);
    } else {
        /* Direct submission if no thread */
        if (pr->rhi_cmd) {
            parallel_renderer_submit(pr, pr->rhi_cmd);
        }
    }
}

void parallel_renderer_wait_submit(ParallelRenderer *pr) {
    if (!pr || !pr->submit_thread_running) {
        return;
    }
    
    pthread_mutex_lock(&pr->submit_mutex);
    while (atomic_load(&pr->submit_pending)) {
        pthread_cond_wait(&pr->submit_done, &pr->submit_mutex);
    }
    pthread_mutex_unlock(&pr->submit_mutex);
}

/* ============================================================ */
/*                            Stats                             */
/* ============================================================ */

u32 parallel_renderer_total_commands(ParallelRenderer *pr) {
    if (!pr) {
        return 0;
    }
    /* Count commands in the write frame (currently being recorded) */
    const FrameCommands *frame = &pr->frames[pr->write_frame];
    u32 total = 0;
    for (u32 i = 0; i < pr->thread_count; ++i) {
        total += frame->buffers[i].count;
    }
    return total;
}
