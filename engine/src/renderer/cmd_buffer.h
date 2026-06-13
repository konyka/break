#pragma once
/*
 * Parallel render command buffer with double-buffered submission.
 *
 * Multiple worker threads each record into a thread-local RenderCmdBuffer
 * (no shared writes -> lock-free recording). At end-of-frame the main thread
 * swaps buffers and signals the submit thread to replay the previous frame's
 * commands while workers record into the next frame's buffers.
 */
#include <core/types.h>
#include <rhi/rhi.h>
#include <stdatomic.h>
#include <pthread.h>
#include <stdbool.h>

#define CMD_BUFFER_MAX_COMMANDS 4096
#define CMD_BUFFER_MAX_THREADS  16
#define CMD_BUFFER_PUSH_CONST_MAX 128

/* ---- Render command type tag ---- */
typedef enum {
    RENDER_CMD_DRAW,
    RENDER_CMD_DRAW_INDEXED,
    RENDER_CMD_BIND_PIPELINE,
    RENDER_CMD_BIND_VERTEX_BUFFER,
    RENDER_CMD_BIND_INDEX_BUFFER,
    RENDER_CMD_BIND_UNIFORM,
    RENDER_CMD_BIND_TEXTURE,
    RENDER_CMD_SET_SCISSOR,
    RENDER_CMD_SET_VIEWPORT,
    RENDER_CMD_PUSH_CONSTANTS,
} RenderCmdType;

/*
 * Encoded render command. The union keeps the struct a fixed size so that
 * arrays of RenderCmd are tightly packed for cache-friendly replay.
 */
typedef struct {
    RenderCmdType type;
    union {
        struct {
            u32 vertex_count;
            u32 instance_count;
            u32 first_vertex;
        } draw;
        struct {
            u32 index_count;
            u32 instance_count;
            u32 first_index;
            i32 vertex_offset;
        } draw_indexed;
        struct {
            RHIPipeline pipeline;
        } bind_pipeline;
        struct {
            RHIBuffer buffer;
            u32       offset;
        } bind_vb;
        struct {
            RHIBuffer buffer;
            u32       offset;
            bool      is_u32;
        } bind_ib;
        struct {
            u32       binding;
            RHIBuffer buffer;
            u32       offset;
            u32       size;
        } bind_uniform;
        struct {
            u32        slot;
            RHITexture texture;
        } bind_texture;
        struct {
            i32 x, y;
            u32 w, h;
        } scissor;
        struct {
            f32 x, y, w, h;
            f32 min_depth, max_depth;
        } viewport;
        struct {
            u32 offset;
            u32 size;
            u8  data[CMD_BUFFER_PUSH_CONST_MAX];
        } push_constants;
    };
} RenderCmd;

/* Thread-local command buffer (one per worker). */
typedef struct {
    RenderCmd commands[CMD_BUFFER_MAX_COMMANDS];
    u32       count;
    u32       sort_key;  /* used to order buffers during submit */
} RenderCmdBuffer;

/* Double-buffered frame state for parallel recording/submission. */
typedef struct {
    RenderCmdBuffer buffers[CMD_BUFFER_MAX_THREADS];
    u32             buffer_count;
    u32             sort_keys[CMD_BUFFER_MAX_THREADS];
} FrameCommands;

/* Parallel renderer: aggregates per-thread buffers with double-buffering. */
typedef struct {
    /* Double-buffered command storage */
    FrameCommands   frames[2];
    u32             write_frame;      /* Index of frame being recorded (0 or 1) */
    u32             read_frame;       /* Index of frame being submitted */
    
    /* Thread synchronization */
    pthread_t       submit_thread;
    pthread_mutex_t submit_mutex;
    pthread_cond_t  submit_ready;
    pthread_cond_t  submit_done;
    _Atomic bool    submit_pending;
    _Atomic bool    shutdown_requested;
    
    /* RHI command buffer for submission (set before begin_frame) */
    RHICmdBuffer   *rhi_cmd;
    
    /* State */
    u32             thread_count;
    _Atomic u32     active_recorders;
    bool            recording;
    bool            submit_thread_running;
} ParallelRenderer;

/* ---- Lifecycle ---- */
void parallel_renderer_init(ParallelRenderer *pr, u32 thread_count);
void parallel_renderer_shutdown(ParallelRenderer *pr);

/* ---- Submit thread control ---- */
bool parallel_renderer_start_submit_thread(ParallelRenderer *pr);
void parallel_renderer_stop_submit_thread(ParallelRenderer *pr);

/* ---- Per-frame flow ---- */
void parallel_renderer_begin_frame(ParallelRenderer *pr);
void parallel_renderer_end_frame(ParallelRenderer *pr);

/*
 * Get the per-thread command buffer for the calling worker.
 * Lock-free: each thread_id maps 1:1 to its own buffer.
 */
RenderCmdBuffer *parallel_renderer_get_buffer(ParallelRenderer *pr, u32 thread_id);

/* ---- Command recording API (writes into the supplied buffer) ---- */
void cmd_draw(RenderCmdBuffer *buf, u32 vertex_count, u32 instance_count, u32 first_vertex);
void cmd_draw_indexed(RenderCmdBuffer *buf, u32 index_count, u32 instance_count,
                      u32 first_index, i32 vertex_offset);
void cmd_bind_pipeline(RenderCmdBuffer *buf, RHIPipeline pipeline);
void cmd_bind_vertex_buffer(RenderCmdBuffer *buf, RHIBuffer buffer, u32 offset);
void cmd_bind_index_buffer(RenderCmdBuffer *buf, RHIBuffer buffer, u32 offset, bool is_u32);
void cmd_bind_uniform(RenderCmdBuffer *buf, u32 binding, RHIBuffer buffer, u32 offset, u32 size);
void cmd_bind_texture(RenderCmdBuffer *buf, u32 slot, RHITexture texture);
void cmd_set_scissor(RenderCmdBuffer *buf, i32 x, i32 y, u32 w, u32 h);
void cmd_set_viewport(RenderCmdBuffer *buf, f32 x, f32 y, f32 w, f32 h, f32 min_d, f32 max_d);
void cmd_push_constants(RenderCmdBuffer *buf, u32 offset, u32 size, const void *data);

/*
 * Set the RHI command buffer for the next submission.
 * Must be called before begin_frame when using submit thread.
 */
void parallel_renderer_set_rhi_cmd(ParallelRenderer *pr, RHICmdBuffer *rhi_cmd);

/*
 * Submit: merge all per-thread buffers (ordered by sort_key) and replay onto
 * the supplied RHI command buffer. Can be called directly or via submit thread.
 */
void parallel_renderer_submit(ParallelRenderer *pr, RHICmdBuffer *rhi_cmd);

/*
 * Swap buffers and signal submit thread (used with double-buffering).
 * Returns immediately; submission happens on submit thread.
 */
void parallel_renderer_swap_and_submit(ParallelRenderer *pr);

/*
 * Wait for pending submission to complete (sync point).
 */
void parallel_renderer_wait_submit(ParallelRenderer *pr);

/* ---- Stats ---- */
u32 parallel_renderer_total_commands(ParallelRenderer *pr);
