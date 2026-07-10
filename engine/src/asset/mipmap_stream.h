#pragma once

#include <core/types.h>
#include <asset/async_loader.h>

/*
 * Mipmap Streaming System
 *
 * Provides visibility-based texture mipmap level streaming:
 * - Tracks texture screen coverage to select optimal mipmap level
 * - Asynchronously loads only required mipmap levels on demand
 * - Reduces memory by keeping only visible mipmap levels resident
 * - Supports priority-based streaming (closer objects get higher priority)
 */

#define MIPMAP_STREAM_MAX_TEXTURES  1024
#define MIPMAP_STREAM_MAX_LEVELS    16
#define MIPMAP_STREAM_REQ_POOL_SIZE 64  /* preallocated request context slots */

typedef enum {
    MIPMAP_LEVEL_UNLOADED = 0,   /* Not loaded, data not in memory */
    MIPMAP_LEVEL_LOADING,        /* Async load in progress */
    MIPMAP_LEVEL_RESIDENT,       /* Data in memory, ready to use */
    MIPMAP_LEVEL_EVICTING        /* Being evicted to free memory */
} MipmapLevelState;

typedef struct {
    char               path[256];
    u32                width;
    u32                height;
    u32                mip_count;
    u32                bytes_per_pixel;
    /* Per-level state */
    MipmapLevelState   level_state[MIPMAP_STREAM_MAX_LEVELS];
    u64                level_request_id[MIPMAP_STREAM_MAX_LEVELS];
    void              *level_data[MIPMAP_STREAM_MAX_LEVELS];
    u32                level_size[MIPMAP_STREAM_MAX_LEVELS];
    u64                level_offset[MIPMAP_STREAM_MAX_LEVELS];  /* byte offset in file — R166-B: u64 to prevent truncation >4GB */
    /* Visibility tracking */
    f32                screen_coverage;   /* 0.0 - 1.0, fraction of screen */
    u32                desired_level;     /* computed from coverage */
    u32                resident_level;    /* highest loaded level */
    u64                last_visible_frame;/* frame number when last seen */
    bool               active;
} StreamedTexture;

/* Called on the main thread (from async_loader_tick) when a mip level's bytes
 * become resident, so the host can push them to the GPU. RGBA8 assumed. */
typedef void (*MipmapUploadFn)(void *ctx, i32 tex_idx, u32 level,
                               u32 width, u32 height, const void *data, u32 size);

typedef struct {
    StreamedTexture    textures[MIPMAP_STREAM_MAX_TEXTURES];
    u32                texture_count;
    /* Memory budget tracking */
    usize              total_resident_bytes;
    usize              memory_budget;       /* max bytes to keep resident */
    /* Statistics */
    u32                load_requests;
    u32                evictions;
    u32                cache_hits;
    u32                uploads;
    bool               ready;
    /* GPU upload hook (optional) */
    MipmapUploadFn     upload_fn;
    void              *upload_ctx;
    /* Request context pool: avoids per-request malloc (24 bytes/slot for MipLoadReq) */
    u8                 req_pool[MIPMAP_STREAM_REQ_POOL_SIZE * 24];
    u32                req_pool_next;  /* next free slot index */
} MipmapStreamManager;

/* Initialize/shutdown the streaming manager */
bool mipmap_stream_init(MipmapStreamManager *mgr, usize memory_budget);
void mipmap_stream_shutdown(MipmapStreamManager *mgr);

/* Register a texture for streaming. Returns texture index or -1 on failure.
 * The file is expected to contain raw mipmap levels sequentially,
 * from mip0 (full res) to mipN (1x1). */
i32 mipmap_stream_register(MipmapStreamManager *mgr, const char *path,
                            u32 width, u32 height, u32 mip_count,
                            u32 bytes_per_pixel);

/* Update visibility for a registered texture.
 * screen_coverage: 0.0 (not visible) to 1.0 (fills entire screen)
 * frame_number: current frame for LRU eviction */
void mipmap_stream_update_visibility(MipmapStreamManager *mgr, i32 tex_idx,
                                      f32 screen_coverage, u64 frame_number);

/* Compute desired mipmap level from screen coverage and request loading.
 * Call once per frame after updating visibility for all textures.
 * Automatically evicts unused levels when memory budget is exceeded. */
void mipmap_stream_update(MipmapStreamManager *mgr);

/* Get the data pointer for a specific mipmap level (NULL if not resident) */
void *mipmap_stream_get_level(MipmapStreamManager *mgr, i32 tex_idx, u32 level);

/* Force load a specific mipmap level synchronously (blocks until ready) */
bool mipmap_stream_force_level(MipmapStreamManager *mgr, i32 tex_idx, u32 level);

/* Register a GPU upload callback, invoked when a level becomes resident. */
void mipmap_stream_set_upload(MipmapStreamManager *mgr, MipmapUploadFn fn, void *ctx);

/* Highest-resolution (lowest index) level currently resident, or mip_count. */
u32 mipmap_stream_resident_level(MipmapStreamManager *mgr, i32 tex_idx);

/* Get statistics */
u32 mipmap_stream_load_requests(MipmapStreamManager *mgr);
u32 mipmap_stream_evictions(MipmapStreamManager *mgr);
u32 mipmap_stream_uploads(MipmapStreamManager *mgr);
usize mipmap_stream_resident_bytes(MipmapStreamManager *mgr);

/* Drop all resident/loading levels for a texture (e.g. after hot-reload). */
void mipmap_stream_invalidate(MipmapStreamManager *mgr, i32 tex_idx);
